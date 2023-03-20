def pid_to_name(pid):
	procCount = gdb.parse_and_eval("theProcessManager.ptr->processes.dataSize")
	for pix in range(procCount):
		cpid = gdb.parse_and_eval("((Process*)theProcessManager.ptr->processes.data[%s].theObject)->pid" % pix)
		if cpid == pid: return gdb.parse_and_eval("((Process*)theProcessManager.ptr->processes.data[%s].theObject)->name.p" % pix)
	return "Unknown PID"

class ThreadsCommand (gdb.Command):

	def __init__ (self):
		super (ThreadsCommand, self).__init__ ("btos-threads", gdb.COMMAND_USER)
		
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
			tname = gdb.parse_and_eval("theScheduler.ptr->threads.data[%s]->name.p" % tix)
			status = gdb.parse_and_eval("theScheduler.ptr->threads.data[%s]->status" % tix)
			# bc = gdb.parse_and_eval("theScheduler.ptr->threads.data[%s]->blockCheck" % tix)
			blockinfo = ""
			# if bc != 0:
			# 	modname = self.addr_to_module(bc)
			# 	bcp = gdb.parse_and_eval("threads.data[%s]->bc_param" % tix)
			# 	blockinfo = "(%s :: %s (%s))" % (modname, bc, bcp)
			name = pid_to_name(pid)
			print("%s (%s) Name: %s: TID: %s PID: %s (%s) Status: %s %s" % (tix, ptr, tname, tid, pid, name, status, blockinfo))

ThreadsCommand ()

class ModsCommand (gdb.Command):
	def __init__ (self):
	   super (ModsCommand, self).__init__ ("btos-modules", gdb.COMMAND_USER)
	
	def invoke (self, arg, from_tty):
		modCount = gdb.parse_and_eval("theModuleManager.ptr->modules.dataSize")
		for mix in range(modCount):
			base = gdb.parse_and_eval("((ElfModule*)(theModuleManager.ptr->modules.data[%s].elf))->mod.mem.aligned" % mix)
			name = gdb.parse_and_eval("theModuleManager.ptr->modules.data[%s].filename.p" % mix)
			print("%s: Module: %s Addr: %s" % (mix, name, base))

ModsCommand ()

class ProcsCommand (gdb.Command):
	def __init__ (self):
		super (ProcsCommand, self).__init__ ("btos-procs", gdb.COMMAND_USER)
	
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
		if pix == '':
			print(gdb.parse_and_eval("((Process*)theProcessManager.ptr->currentProcess)"))
			print(gdb.parse_and_eval("*((Process*)theProcessManager.ptr->currentProcess)"))
		else:
			print(gdb.parse_and_eval("((Process*)theProcessManager.ptr->processes.data[%s].theObject)" % pix))
			print(gdb.parse_and_eval("*((Process*)theProcessManager.ptr->processes.data[%s].theObject)" % pix))
	
ProcCommand ()

class ThreadCommand (gdb.Command):
	def __init__ (self):
		super (ThreadCommand, self).__init__ ("btos-thread", gdb.COMMAND_USER)
	
	def invoke (self, arg, from_tty):
		tix = arg
		if tix == '':
			print(gdb.parse_and_eval("theScheduler.ptr->current"))
			print(gdb.parse_and_eval("*theScheduler.ptr->current"))
		else:
			print(gdb.parse_and_eval("theScheduler.ptr->threads.data[%s]" % tix))
			print(gdb.parse_and_eval("*theScheduler.ptr->threads.data[%s]" % tix))
	
ThreadCommand ()

class MessagesCommand (gdb.Command):
	def __init__ (self):
		super (MessagesCommand, self).__init__ ("btos-messages", gdb.COMMAND_USER)
	
	def invoke (self, arg, from_tty):
		msgCount = gdb.parse_and_eval("theMessageManager.ptr->messages.dataSize")
		for mix in range(msgCount):
			ptr = gdb.parse_and_eval("&theMessageManager.ptr->messages.data[%s]" % mix)
			msgId = gdb.parse_and_eval("theMessageManager.ptr->messages.data[%s].header.id" % mix)
			msgFrom = gdb.parse_and_eval("theMessageManager.ptr->messages.data[%s].header.from" % mix)
			fromName = pid_to_name(msgFrom)
			msgTo = gdb.parse_and_eval("theMessageManager.ptr->messages.data[%s].header.to" % mix)
			toName = pid_to_name(msgTo)
			reply = gdb.parse_and_eval("theMessageManager.ptr->messages.data[%s].header.reply_id" % mix)
			msgType = gdb.parse_and_eval("theMessageManager.ptr->messages.data[%s].header.type" % mix)
			msgLen = gdb.parse_and_eval("theMessageManager.ptr->messages.data[%s].header.length" % mix)
			flags = gdb.parse_and_eval("theMessageManager.ptr->messages.data[%s].header.flags" % mix)
			print("%s (%s): ID: %s From: %s (%s) To: %s (%s) Reply: %s Type: %s Len: %s Flags: %s" % 
				(mix, ptr, msgId, msgFrom, fromName, msgTo, toName, reply, msgType, msgLen, hex(flags))
			)

MessagesCommand ()

class BlockCommand (gdb.Command):
	def __init__ (self):
		super (BlockCommand, self).__init__ ("btos-block", gdb.COMMAND_USER)
	
	def invoke (self, arg, from_tty):
		tix = arg
		if tix == '':
			addr = gdb.parse_and_eval("theScheduler.ptr->current")
		else:
			addr = gdb.parse_and_eval("theScheduler.ptr->threads.data[%s]" % tix)
		fnAddr = gdb.parse_and_eval("&({Thread}%s).blockCheck" % addr)
		print(fnAddr)
		print(gdb.parse_and_eval("({function<bool()>}%s)" % fnAddr))
		print(gdb.parse_and_eval("{void*}({function<bool()>}%s).callableBuffer" % fnAddr))

BlockCommand ()