#ifndef JOS_KERN_E1000_H
#define JOS_KERN_E1000_H

#include <inc/string.h>
#include <kern/pci.h>
#include <kern/e1000_hw.h>
#include <kern/pmap.h>

#define TXRING_LEN 32
#define RXRING_LEN 32




int pci_e1000_attach(struct pci_func *pcif);
int e1000_transmit(void *addr, uint16_t len);

#endif	// JOS_KERN_E1000_H
