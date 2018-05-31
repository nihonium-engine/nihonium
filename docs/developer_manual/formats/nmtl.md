# NMTL Format Specification

**This version:** 1

## Introduction

The NMTL (**N**ihonium **M**a**t**eria**l**) format is a file format used for storing materials for the Nihonium Game Engine.  
NMTL files should have the '.nmtl' file extension.

**Note:** All multi-byte values are in little endian format.

## Basic Structure

Each material consists of five values: albedo (colour), normal, metallic, roughness and ambient occlusion (AO).

Each of these values can be either a single value or it can be a map (texture).

|Field           |Size    |Description                                                                                     |
|----------------|--------|------------------------------------------------------------------------------------------------|
|Magic           |4 bytes |Magic string used to identify an NMTL file. Always "NMTL" in ASCII (0x4E 0x4D 0x54 0x4C).       |
|Version         |4 bytes |Used to identify the version. For this version, it should be 0x00000001.                        |
|Value Types     |8 bytes |Each byte represents whether the corresponding value is a single value or map (see Value Types).|
|Values          |Variable|See Value Structure for a full description of this field.                                       | 

# Value Types

The Value Types field consists of 8 bytes. Currently, only 5 of these are used.  
A 0 means that a single value is used; any other value means a map is used.

|Byte|Value    |
|----|---------|
|0   |Albedo   |
|1   |Normal   |
|2   |Metallic |
|3   |Roughness|
|4   |AO       |
|5-7 |Unused   |

# Value Structure

As previously stated, the material consists of five values, each of which is either a single value or map.  

For a single value, the value should be three single-precision numbers in the case of albedo or normal, or one in the case of metallic, roughness and AO.

For a map, the value should be a 4-byte integer with the length of the path to the image in bytes, which should be followed by the path itself.
