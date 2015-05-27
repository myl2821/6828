#include <kern/e1000.h>

// LAB 6: Your driver code here

#define BUFFSIZE 2048

char *test = "TEST";

char *e1000_8t;
uint32_t *e1000_32t;

struct e1000_tx_desc tx_ring[TXRING_LEN] __attribute__ ((aligned (128)));
char e1000_tx_buf[TXRING_LEN][BUFFSIZE];

struct e1000_rx_desc rx_ring[RXRING_LEN] __attribute__ ((aligned (128)));
char e1000_rx_buf[RXRING_LEN][BUFFSIZE];

static inline void tx_init()
{
	// just follow guide on 14.5

	// use PADDR so user env can also get access to it
	e1000_32t[E1000_TDBAL/4] = PADDR(tx_ring);
	e1000_32t[E1000_TDBAH/4] = 0;
	e1000_32t[E1000_TDLEN/4] = TXRING_LEN * sizeof(struct e1000_tx_desc);
	e1000_32t[E1000_TDT/4] = 0;
	e1000_32t[E1000_TDH/4] = 0;
	e1000_32t[E1000_TIPG/4] = 10 | (8<<10) | (6<<20);
	e1000_32t[E1000_TCTL/4] = E1000_TCTL_EN|
		E1000_TCTL_PSP|
		(E1000_TCTL_CT & (0x10 << 4))|
		(E1000_TCTL_COLD & (0x40 << 12));
	
	int i;
	for(i = 0; i < TXRING_LEN; i++) {
		memset(&tx_ring[i], 0, sizeof(struct e1000_tx_desc));
		tx_ring[i].buffer_addr = PADDR(e1000_tx_buf[i]);
		tx_ring[i].upper.fields.status = E1000_TXD_STAT_DD;
		tx_ring[i].lower.flags.cmd = E1000_TXD_CMD_RS|E1000_TXD_CMD_EOP;
	}
}

int e1000_transmit(void *addr, uint16_t len)
{
	uint32_t tail = e1000_32t[E1000_TDT/4];
	struct e1000_tx_desc *next = &tx_ring[tail];
	if (!(next->upper.fields.status & E1000_TXD_STAT_DD))
		return -1;
	memcpy(e1000_tx_buf[tail], addr, len);
	next->lower.flags.length = len;
	next->upper.fields.status &= !E1000_TXD_STAT_DD;
	e1000_32t[E1000_TDT/4] = (tail+1) % TXRING_LEN;

	return 0;
}

int pci_e1000_attach(struct pci_func *pcif)
{
	pci_func_enable(pcif);
	e1000_8t = (char *)mmio_map_region(pcif->reg_base[0],	pcif->reg_size[0]);
	e1000_32t = (uint32_t *)e1000_8t;
	tx_init();

	cprintf("e1000: status %x\n", e1000_32t[E1000_STATUS / 4]);
	return 1;
}

