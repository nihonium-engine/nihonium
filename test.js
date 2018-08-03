var model_source = filesystem.open("main:test.nmdl");
var mat_source = filesystem.open("main:test_material.json");

var my_model = model.load(model_source);

var my_material = material.load(mat_source);

function update(delta_time) {

  var pos = vec3.new(0, 0, -5);
  var rot = quat.from_euler(30 / 180 * Math.PI, 30 / 180 * Math.PI, 30 / 180 * Math.PI);
  var scale = vec3.new(1, 0.5, 1.5)

  render.render(my_model, my_material, pos, rot, scale);

}

function draw() {

}
