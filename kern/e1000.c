#include <kern/e1000.h>

// LAB 6: Your driver code here

#include <kern/pmap.h>

char *e1000_8t;
uint32_t *e1000_32t;

int pci_e1000_attach(struct pci_func *pcif)
{
	pci_func_enable(pcif);
	e1000_8t = (char *)mmio_map_region(pcif->reg_base[0],	pcif->reg_size[0]);
	e1000_32t = (uint32_t *)e1000_8t;
	cprintf("e1000: status %x\n", e1000_32t[E1000_STATUS / 4]);
	return 1;
}

