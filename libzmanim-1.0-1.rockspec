package = 'Libzmanim'
version = '1.0-1'
source = {
   url = "git://github.com/yparitcher/libzmanim",
}
description = {
   summary = 'Libzmanim',
   detailed = [[
      Libzmanim
   ]],
   homepage = 'paritcher.com',
   maintainer = 'Yparitcher',
   license = 'MIT'
}
dependencies = {
   'lua >= 5.1'
}
build = {
   type = 'make',
   build_target = 'rock',
   build_variables = {
      CC="$(CC)",
   },
   install_variables = {
      INST_LIBDIR="$(LIBDIR)",
      INST_LUADIR="$(LUADIR)",
   },
}

