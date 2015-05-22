// implement fork from user space

#include <inc/string.h>
#include <inc/lib.h>

// PTE_COW marks copy-on-write page table entries.
// It is one of the bits explicitly allocated to user processes (PTE_AVAIL).
#define PTE_COW		0x800

//
// Custom page fault handler - if faulting page is copy-on-write,
// map in our own private writable copy.
//
static void
pgfault(struct UTrapframe *utf)
{
	void *addr = (void *) utf->utf_fault_va;
	uint32_t err = utf->utf_err;

	// Check that the faulting access was (1) a write, and (2) to a
	// copy-on-write page.  If not, panic.
	// Hint:
	//   Use the read-only page table mappings at uvpt
	//   (see <inc/memlayout.h>).

	// LAB 4: Your code here.

	assert(err & FEC_WR);
	assert(err & FEC_U);
	assert(uvpd[PDX(addr)] & PTE_P);
	assert(uvpt[PGNUM(addr)] & PTE_P);
	assert(uvpt[PGNUM(addr)] & PTE_COW);

	// Allocate a new page, map it at a temporary location (PFTEMP),
	// copy the data from the old page to the new page, then move the new
	// page to the old page's address.
	// Hint:
	//   You should make three system calls.

	// LAB 4: Your code here.
	
	// we MUST ROUNDDOWN addr to copy whole page in 'memmove'
	// and mapping it to new va
	addr = ROUNDDOWN(addr, PGSIZE);

	assert(sys_page_alloc(0, PFTEMP, PTE_W|PTE_U|PTE_P) == 0);
	memmove(PFTEMP, addr, PGSIZE);
	assert(sys_page_map(0, PFTEMP, 0, addr, PTE_W|PTE_U|PTE_P) == 0);
	assert(sys_page_unmap(0, PFTEMP) == 0);
	return;
}

//
// Map our virtual page pn (address pn*PGSIZE) into the target envid
// at the same virtual address.  If the page is writable or copy-on-write,
// the new mapping must be created copy-on-write, and then our mapping must be
// marked copy-on-write as well.  (Exercise: Why do we need to mark ours
// copy-on-write again if it was already copy-on-write at the beginning of
// this function?)
//
// Returns: 0 on success, < 0 on error.
// It is also OK to panic on error.
//
static int
duppage(envid_t envid, unsigned pn)
{
	// LAB 4: Your code here.
	void *addr = (void *)(pn * PGSIZE);
	uint32_t perm = PGOFF(uvpt[pn]);
	uint32_t cow_perm = PTE_COW|(perm & ~PTE_W);
	if ((uvpt[pn] & PTE_W) || (uvpt[pn] & PTE_COW)) {
		assert(sys_page_map(0, addr, envid, addr, cow_perm) == 0);
		assert(sys_page_map(0, addr, 0, addr, cow_perm) == 0);
	} else {
		assert(sys_page_map(0, addr, envid, addr, perm) == 0);
	}
	return 0;
}

//
// User-level fork with copy-on-write.
// Set up our page fault handler appropriately.
// Create a child.
// Copy our address space and page fault handler setup to the child.
// Then mark the child as runnable and return.
//
// Returns: child's envid to the parent, 0 to the child, < 0 on error.
// It is also OK to panic on error.
//
// Hint:
//   Use uvpd, uvpt, and duppage.
//   Remember to fix "thisenv" in the child process.
//   Neither user exception stack should ever be marked copy-on-write,
//   so you must allocate a new page for the child's user exception stack.
//
envid_t
fork(void)
{
	// LAB 4: Your code here.

	// set up global pgfault handler for user space.
	set_pgfault_handler(pgfault);

	// steal code from dumbfork...
	envid_t envid = sys_exofork();
	uint32_t addr;
	assert(envid >= 0);
	if (envid == 0) {
		thisenv = &envs[ENVX(sys_getenvid())];
		return 0;
	}

	// [USTACKTOP, UXSTACKTOP) is belong to user exception stack.
	// exception stack CANNOT be marked COW.
	for (addr = 0; addr < USTACKTOP; addr += PGSIZE) {
		if ((uvpd[PDX(addr)] & PTE_P)
				&& (uvpt[PGNUM(addr)] & PTE_P)
				&& (uvpt[PGNUM(addr)] & PTE_U)) {
			duppage(envid, PGNUM(addr));
		}
	}

	assert(sys_page_alloc(envid, (void *)(UXSTACKTOP-PGSIZE), PTE_U|PTE_W|PTE_P) == 0);

	// MUST set it explicitly for child.
	extern void _pgfault_upcall();
	sys_env_set_pgfault_upcall(envid, _pgfault_upcall);

	assert(sys_env_set_status(envid, ENV_RUNNABLE) == 0);

	return envid;
}

// Challenge!
int
sfork(void)
{
	panic("sfork not implemented");
	return -E_INVAL;
}
