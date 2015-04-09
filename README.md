6.828 teaches the fundamentals of engineering operating systems. You will study, in detail, virtual memory, kernel and user mode, system calls, threads, context switches, interrupts, interprocess communication, coordination of concurrent activities, and the interface between software and hardware. Most importantly, you will study the interactions between these concepts, and how to manage the complexity introduced by the interactions.

To master the concepts, 6.828 is organized in three parts: lectures, readings, and a major lab. The lectures and readings familiarize you with the main concepts. The lab forces you to understand the concepts at a deep level, since you will build an operating system from the ground up. After the lab you will appreciate the meaning of design goals such "reducing complexity" and "conceptual integrity".

The lectures are organized in two main blocks. The first block introduces one operating system, xv6 (x86 version 6), which is a re-implementation of Unix Version 6, which was developed in the 1970s. In each lecture we will take one part of xv6 and study its source code; homework assignments will help you prepare for these lectures. At the end of the first block (about half-way the term), you will understand the source code for one well-designed operating system for an Intel-based PC, which help you building your own operating system.

The second block of lectures covers important operating systems concepts invented after Unix v6. We will study the more modern concepts by reading research papers and discussing them in lecture. You will also implement some of these newer concepts in your operating system.

You may wonder why we are studying an operating system that resembles Unix v6 instead of the latest and greatest version of Linux, Windows, or BSD Unix. xv6 is big enough to illustrate the basic design and implementation ideas in operating systems. On the other hand, xv6 is far smaller than any modern production O/S, and correspondingly easier to understand. xv6 has a structure similar to many modern operating systems; once you've explored xv6 you will find much that is familiar inside kernels such as Linux.

The lab is the place where the rubber meets the road. In the lab you will internalize the details of the concepts and their interactions. For example, although you have seen virtual memory in 6.004, 6.033, and again in 6.828 lectures, you will soon discover, during the labs, that you didn't really understand virtual memory and how it interacts with other concepts.

The lab is split into 6 major parts that build on each other, culminating in a primitive operating system on which you can run simple commands through your own shell. We reserve the last lecture for you to demo your operating system to the rest of the class.

The operating system you will build, called JOS, will have Unix-like functions (e.g., fork, exec), but is implemented in an exokernel style (i.e., the Unix functions are implemented mostly as user-level library instead of built-in to the kernel). The major parts of the JOS operating system are:

Booting
Memory management
User environments
Preemptive multitasking
File system, spawn, and shell
Network driver
Open-ended project
We will provide skeleton code for pieces of JOS, but you will have to do all the hard work. You'll have design freedom for the details of the first few assignments, and freedom over the whole design in the last assignments. You'll find that xv6 helps you understand many of the goals you're trying to achieve in JOS, but that JOS occupies a very different point in the design and implementation space from xv6.

The first 6 assignments are done individually. The last assignment is a team assignment.

You will develop your JOS operating system for a standard x86-based personal computer, the same one used for xv6. To simplify development we will use a complete machine simulator (QEMU) in the class for development and debugging. This simulator is real enough, however, that you will be able to boot your own operating system on physical hardware if you wish.

At the end of the lab you will be able to find your way around the source code of most operating systems, and more generally, be comfortable with system software. You will understand many operating systems concepts in detail and will be able to use them in other environments. You will also understand the x86 processor and the C programming language well.

Acknowledgements
6.828 would not exist today had it not been for a wonderful set of past TAs (Josh Cates, Austin Clements, Russ Cox, Bryan Ford, Max Krohn, and Emil Sit). They made this class a reality. Collectively we dedicate 6.828 to the memory of Josh Cates; We hope that many students will be inspired by Josh's enthusiasm for operating systems, and have named the operating system JOS. We are also grateful to the students and teaching staff at Harvard, MIT (including SIPB), UCLA, and NYU for their many contributions.
