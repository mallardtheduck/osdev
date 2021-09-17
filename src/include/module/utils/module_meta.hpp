#ifndef MODULE_META_HPP
#define MODULE_META_HPP

#ifdef KERNEL
	#define KERNEL_ONLY(x) x
#else
	#define KERNEL_ONLY(x)
#endif

#ifdef KERNEL_MODULE
	#define MODULE_ONLY(x) x
#else
	#define MODULE_ONLY(x)
#endif

#endif