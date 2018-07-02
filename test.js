var model_source = filesystem.open("main:test.nmdl")
var mat_source = filesystem.open("main:test_material.json")

var my_model = model.load(model_source)

var my_material = material.load(mat_source)

function update(delta_time) {

  render.render(my_model, my_material)

}

function draw() {

}
