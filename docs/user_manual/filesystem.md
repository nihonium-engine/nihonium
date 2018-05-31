# Nihonium Documentation

## Filesystem

### Introduction
Nihonium is not able to directly access the user's files. Instead, it uses its own *virtual filesystem*, which is quite similar to the DOS- and Windows-like filesystem.

The filesystem is organised into one or more *'mounts'*, which are analogous to drives on DOS and Windows.

A mount may be a .nar file or an actual directory on the user's system.

There is always at least one mount present, which is called `main`.

### Path Names

Paths in Nihonium are similar to paths in other filesystems, and are structured like this:
```
mount:/path/to/file
```

The name of the mount comes first, followed by a colon (':'). This is then followed by the path.  
Paths use the forward slash ('/') as a directory separator, and begin with a leading directory separator.
