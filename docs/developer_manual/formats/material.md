# Nihonium Material Format Specification

**This version:** 1

## 1: Introduction

The Nihonium Material Format is a JSON-based format used for storing materials for use in rendering.
These materials consist of a the shaders to use and a set of parameters to pass to the shaders.
As Nihonium supports arbitrarily programmed shaders, there is no restriction on what parameters can be represented.
In most cases, the built-in PBR shader will be used. An example of the parameters required for this shader is given in Appendix A.

## 2: Basic Structure

This format is very simple, so it is probably best to show an example first.
```json
{
  "version": 1,
  "vertex_shader": "main:shaders/vertex_shader.vert",
  "fragment_shader": "main:shaders/fragment_shader.frag",
  "parameters": [
    {
      "name": "diffuse",
      "type": "map",
      "components": 3,
      "path": "main:textures/diffuse_map.png"
    },
    {
      "name": "specular",
      "type": "single",
      "value": [
        1.0,
        0.5,
        0.75
      ]
    },
    {
      "name": "specular_exp",
      "type": "single",
      "value": [
        3.0
      ]
    }
  ]
}
```

Now, to explain:
* The top-level value of a material must be an object.
* This top-level object must contain four keys: `version`, `vertex_shader`, `fragment_shader` and `parameters`.
* The value of `version` must be a number and corresponds to the version of this specification. See *This version* at the top for the current version. 
* The values of `vertex_shader` and `fragment_shader` must be strings. These strings represent paths to the vertex and fragment shaders to be used, respectively.

* The value of `parameters` must be an array.
* Each value in `parameters` represents a variable which is passed on to the shader and must be an object.
* Each value in `parameters` must have a `name` and `type` parameter.
* Each variable can have one of two values for `type`: `map` or `single`. `map` means that the value for each pixel will be obtained from a texture, while `single` means that the same value will be used for every pixel.
* For a map, a `components` and `path` must additionally be specified. `components` is how many components (e.g. red, green, blue, alpha) you want to be able to obtain from the map. `path` is the path to the image to use as a map.
* For a single, only a `value` must additionally be specified. `value` must be an array of numbers, where each number corresponds to a component.

## Appendix A: Example material for built-in PBR shader

```json
{
  "version": 1,
  "vertex_shader": "nh:shaders/pbr_vert.vert",
  "fragment_shader": "nh:shaders/pbr_frag.frag",
  "parameters": [
    {
      "name": "albedo",
      "type": "map",
      "components": 3,
      "path": "main:path/to/albedo.png"
    },
    {
      "name": "normal",
      "type": "map",
      "components": 3,
      "path": "main:path/to/normal.png"
    },
    {
      "name": "metallic",
      "type": "map",
      "components": 1,
      "path": "main:path/to/metallic.png"
    },
    {
      "name": "roughness",
      "type": "map",
      "components": 1,
      "path": "main:path/to/roughness.png"
    },
    {
      "name": "ao",
      "type": "map",
      "components": 1,
      "path": "main:path/to/ao.png"
    }
  ]
}
```
