var file = filesystem.open("main:vert.vert")
log.log_info(file.ptr)

filesystem.close(file)
log.log_info(file.ptr)
