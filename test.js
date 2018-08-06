var model_source = filesystem.open("main:test.nmdl");
var mat_source = filesystem.open("main:test_material.json");

var my_model = model.load(model_source);

var my_material = material.load(mat_source);

camera.new("main");
camera.set_enabled("main", true);

var cam_x = 0;
var cam_y = 0;
var cam_z = 0;

var camera_rot_x = 0
var camera_rot_y = 0

function update(delta_time) {

  var pos = vec3.new(0, 0, -5);
  var rot = quat.from_euler(0.00001, 0, 0);
  var scale = vec3.new(1, 0.5, 1.5);

  if (input.is_down("w")) {
    cam_z -= 0.05;
  }
  if (input.is_down("s")) {
    cam_z += 0.05;
  }
  if (input.is_down("a")) {
    cam_x -= 0.05;
  }
  if (input.is_down("d")) {
    cam_x += 0.05;
  }
  if (input.is_down("q")) {
    cam_y -= 0.05;
  }
  if (input.is_down("e")) {
    cam_y += 0.05;
  }

  if (input.is_down("left")) {
    camera_rot_x -= 0.01
  }
  if (input.is_down("right")) {
    camera_rot_x += 0.01
  }
  if (input.is_down("up")) {
    camera_rot_y -= 0.01
  }
  if (input.is_down("down")) {
    camera_rot_y += 0.01
  }

  camera.set_position("main", vec3.new(cam_x, cam_y, cam_z));
  camera.set_rotation("main", quat.from_euler(camera_rot_y, camera_rot_x, 0));

  render.render(my_model, my_material, pos, rot, scale);

}

function draw() {

}
