var model_source = filesystem.open("main:test.nmdl")
var vert_source = filesystem.open("main:vert.vert")
var frag_source = filesystem.open("main:frag.frag")

var my_model = model.load(model_source)
var my_shader = shader.load(vert_source, frag_source)

function update(delta_time) {

  log.log_info(delta_time)

}

function draw() {

}
