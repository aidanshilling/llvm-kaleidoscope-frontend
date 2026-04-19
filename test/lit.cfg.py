import os
import lit.formats

config.name = "kaleidoscope"
config.test_format = lit.formats.ShTest()
config.suffixes = ['.test']

build_dir = lit_config.params.get("build_dir")
filecheck = lit_config.params.get("filecheck")
config.substitutions.append(("%lexer-dump", os.path.join(build_dir, "lexer_dump")))
config.substitutions.append(("%FileCheck", filecheck))
