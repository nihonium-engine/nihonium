# Nihonium Material Format Specification

**This version:** 1

## Introduction

The Nihonium Material Format is a JSON-based format used for storing materials for use in rendering.
As Nihonium supports arbitrarily programmed shaders, there is no restriction on what parameters can be represented.
In most cases, the built-in PBR shader will be used. An example of the parameters required for this shader is given in Appendix A.

## Basic Structure

This format is very simple, so it is probably best to show an example first.
```json
{
  "diffuse": {
    "type": "map",
    "components": 3,
    "path": "main:textures/diffuse_map.png"
  },
  "specular": {
    "type": "single",
    "components": 3,
    "value": [
      1.0,
      0.5,
      0.75,
    ]
  },
  "specular_exp": {
    "type": "single",
    "value": 3.0
  }
}
```

Now, to explain:
* The top-level value of a material must be an object.
* Each value represents a variable which is passed on to the shader. The name of the variable in the shader will be `nh_<key>_<type>`.
* Each value can be one of two types: a `map` or a `single`. `map` means that the value for each pixel will be obtained from a texture, while `single` means that the same value will be used for every pixel.
* For a map, a 'components' and 'path' must be specified. 'components' is how many components (e.g. red, green, blue, alpha) you want to be able to obtain from the map. 'path' is the path to the image to use as a map.
* For a single, only a 'value' must be specified. 'value' can be either a number, or an array of numbers. In the latter case, each number corresponds to a component. A number by itself is equivalent to an array containining that number only.

## Appendix A: Example material for built-in PBR shader

```json
{
  "albedo": {
    "type": "map",
    "components": 3,
    "path": "main:path/to/albedo.png"
  },
  "normal": {
    "type": "map",
    "components": 3,
    "path": "main:path/to/normal.png"
  },
  "metallic": {
    "type": "map",
    "components": 1,
    "path": "main:path/to/metallic.png"
  },
  "roughness": {
    "type": "map",
    "components": 1,
    "path": "main:path/to/roughness.png"
  },
  "ao": {
    "type": "map",
    "components": 1,
    "path": "main:path/to/ao.png"
  }
}
```
