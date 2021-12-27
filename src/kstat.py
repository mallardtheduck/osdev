class ThreadsCommand (gdb.Command):

	def __init__ (self):
		super (ThreadsCommand, self).__init__ ("btos-threadinfo", gdb.COMMAND_USER)
		
	def pid_to_name(self, pid):
		# procCount = gdb.parse_and_eval("proc_processes.dataSize")
		# for pix in range(procCount):
		# 	cpid = gdb.parse_and_eval("proc_processes.data[%s]->pid" % pix)
		# 	if cpid == pid: return gdb.parse_and_eval("proc_processes.data[%s]->name.p" % pix)
		return "Unknown PID"
		
	def addr_to_module(self, addr):
		modCount = gdb.parse_and_eval("theModuleManager.ptr->modules.dataSize")
		ret = "KERNEL"
		modules = []
		for mix in range(modCount):
			base = gdb.parse_and_eval("((ElfModule*)(theModuleManager.ptr->modules.data[%s].elf))->mod.mem.aligned" % mix)
			name = gdb.parse_and_eval("theModuleManager.ptr->modules.data[%s].filename.p" % mix)
			modules.append({'base': base, 'name': name})
		modules.sort(key=lambda x: x['base'])

		for mod in modules:
			if mod['base'] < addr: ret = mod['name'] 
			else: return ret
		return ret

	def invoke (self, arg, from_tty):
		current = gdb.parse_and_eval("theScheduler.ptr->current")
		print("Current thread: %s" % current)
		threadCount = gdb.parse_and_eval("theScheduler.ptr->threads.dataSize")
		for tix in range(threadCount):
			ptr = gdb.parse_and_eval("theScheduler.ptr->threads.data[%s]" % tix)
			tid = gdb.parse_and_eval("theScheduler.ptr->threads.data[%s]->id" % tix)
			pid = gdb.parse_and_eval("theScheduler.ptr->threads.data[%s]->pid" % tix)
			status = gdb.parse_and_eval("theScheduler.ptr->threads.data[%s]->status" % tix)
			# bc = gdb.parse_and_eval("theScheduler.ptr->threads.data[%s]->blockCheck" % tix)
			blockinfo = ""
			# if bc != 0:
			# 	modname = self.addr_to_module(bc)
			# 	bcp = gdb.parse_and_eval("threads.data[%s]->bc_param" % tix)
			# 	blockinfo = "(%s :: %s (%s))" % (modname, bc, bcp)
			name = self.pid_to_name(pid)
			print("%s (%s): TID: %s PID: %s (%s) Status: %s %s" % (tix, ptr, tid, pid, name, status, blockinfo))

ThreadsCommand ()

class ModsCommand (gdb.Command):
	def __init__ (self):
	   super (ModsCommand, self).__init__ ("btos-modinfo", gdb.COMMAND_USER)
	
	def invoke (self, arg, from_tty):
		modCount = gdb.parse_and_eval("theModuleManager.ptr->modules.dataSize")
		for mix in range(modCount):
			base = gdb.parse_and_eval("((ElfModule*)(theModuleManager.ptr->modules.data[%s].elf))->mod.mem.aligned" % mix)
			name = gdb.parse_and_eval("theModuleManager.ptr->modules.data[%s].filename.p" % mix)
			print("%s: Module: %s Addr: %s" % (mix, name, base))

ModsCommand ()

class ProcsCommand (gdb.Command):
	def __init__ (self):
		super (ProcsCommand, self).__init__ ("btos-procinfo", gdb.COMMAND_USER)
	
	def invoke (self, arg, from_tty):
		procCount = gdb.parse_and_eval("theProcessManager.ptr->processes.dataSize")
		for pix in range(procCount):
			ptr = gdb.parse_and_eval("((Process*)theProcessManager.ptr->processes.data[%s].theObject)" % pix)
			pid = gdb.parse_and_eval("((Process*)theProcessManager.ptr->processes.data[%s].theObject)->pid" % pix)
			name = gdb.parse_and_eval("((Process*)theProcessManager.ptr->processes.data[%s].theObject)->name.p" % pix)
			status = gdb.parse_and_eval("((Process*)theProcessManager.ptr->processes.data[%s].theObject)->status" % pix)
			print("%s (%s): PID: %s Name: %s Status: %s" % (pix, ptr, pid, name, status))

ProcsCommand ()

class ProcCommand (gdb.Command):
	def __init__ (self):
		super (ProcCommand, self).__init__ ("btos-proc", gdb.COMMAND_USER)
	
	def invoke (self, arg, from_tty):
		pix = arg
		print(gdb.parse_and_eval("*((Process*)theProcessManager.ptr->processes.data[%s].theObject)" % pix))
	
ProcCommand ()

class ThreadCommand (gdb.Command):
	def __init__ (self):
		super (ThreadCommand, self).__init__ ("btos-thread", gdb.COMMAND_USER)
	
	def invoke (self, arg, from_tty):
		tix = arg
		print(gdb.parse_and_eval("*theScheduler.ptr->threads.data[%s]" % tix))
	
ThreadCommand ()