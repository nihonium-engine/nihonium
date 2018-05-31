# NAR Format Specification

**This version:** 1

## Introduction

The NAR (Nihonium ARchive) format is an archive file format used for storing files for the Nihonium Game Engine.  

Its main features are:
* Minimal overhead - No unneccesary data such as timestamps, permissions etc.
* Support for large files - Supports files up to 16EiB in size.
* Built-in support for compression - Each file can be individually compressed, or not compressed at all.

NAR files should have the '.nar' file extension.  

**Note:** All multi-byte values are in little endian format.

## Basic Structure
|Field|Size|Description|
|---|---|---|
|Magic|3 bytes|Magic string used to identify a NAR archive. Always "NAR" in ASCII (0x4E 0x41 0x52).|
|Version|1 bytes|Used to identify the version. For this version, it should be 0x01.|
|Number of Files|4 bytes|The number of files in the archive.|
|Files|Variable|A series of file entries (see File Entry Format below).|

## File Entry Format
|Field|Size|Description|
|---|---|---|
|File Name Length|4 bytes|The length of the name of the file, in bytes.|
|File Contents Length|8 bytes|The length of the contents of the file in bytes, as it is stored (i.e. after compression etc.).|
|Metadata|8 bytes|Extra information about the file (see File Metadata Format below).|
|File Name|'File Name Length' bytes|The full (absolute) name of the file, encoded as UTF-8. It should use the "/" character (U+002F) as a directory separator. It should start with a single "/" character, but should not contain any trailing "/" characters.|
|File Contents|'File Contents Length' bytes|The contents of the file.|

## File Metadata Format
|Byte(s)|Description|
|---|---|
|0|The compression format used. See Compression Formats below for what each value means.|
|1-7|Reserved for future use.|

## Compression Formats
|Value|Format|
|---|---|
|`0x00`|Uncompressed|
|`0x01`|DEFLATE|

All other values are invalid.