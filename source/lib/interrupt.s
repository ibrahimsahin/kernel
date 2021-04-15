.global osdk_lock
.global osdk_unlock

osdk_lock:
	cli
	ret

osdk_unlock:
	sti
	ret

