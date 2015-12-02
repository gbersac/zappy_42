
# pex
echo "#include \"cmd.h\"" > gfx_pex.c
echo "" >> gfx_pex.c
echo "int\tgfx_pex(t_env *env)" >> gfx_pex.c
echo "{" >> gfx_pex.c
echo "\tchar\t*to_send;" >> gfx_pex.c
echo "" >> gfx_pex.c
echo "\tto_send = (char*)malloc(4);" >> gfx_pex.c
echo "\tmemcpy(to_send, \"pex \", 4);" >> gfx_pex.c
echo "\tsend_cmd_to_graphics(env, to_send);" >> gfx_pex.c
echo "\treturn 1;" >> gfx_pex.c
echo "}" >> gfx_pex.c
echo "" >> gfx_pex.c

# pbc
echo "#include \"cmd.h\"" > gfx_pbc.c
echo "" >> gfx_pbc.c
echo "int\tgfx_pbc(t_env *env)" >> gfx_pbc.c
echo "{" >> gfx_pbc.c
echo "\tchar\t*to_send;" >> gfx_pbc.c
echo "" >> gfx_pbc.c
echo "\tto_send = (char*)malloc(4);" >> gfx_pbc.c
echo "\tmemcpy(to_send, \"pbc \", 4);" >> gfx_pbc.c
echo "\tsend_cmd_to_graphics(env, to_send);" >> gfx_pbc.c
echo "\treturn 1;" >> gfx_pbc.c
echo "}" >> gfx_pbc.c
echo "" >> gfx_pbc.c

# pie
echo "#include \"cmd.h\"" > gfx_pie.c
echo "" >> gfx_pie.c
echo "int\tgfx_pie(t_env *env)" >> gfx_pie.c
echo "{" >> gfx_pie.c
echo "\tchar\t*to_send;" >> gfx_pie.c
echo "" >> gfx_pie.c
echo "\tto_send = (char*)malloc(4);" >> gfx_pie.c
echo "\tmemcpy(to_send, \"pie \", 4);" >> gfx_pie.c
echo "\tsend_cmd_to_graphics(env, to_send);" >> gfx_pie.c
echo "\treturn 1;" >> gfx_pie.c
echo "}" >> gfx_pie.c
echo "" >> gfx_pie.c

# pfk
echo "#include \"cmd.h\"" > gfx_pfk.c
echo "" >> gfx_pfk.c
echo "int\tgfx_pfk(t_env *env)" >> gfx_pfk.c
echo "{" >> gfx_pfk.c
echo "\tchar\t*to_send;" >> gfx_pfk.c
echo "" >> gfx_pfk.c
echo "\tto_send = (char*)malloc(4);" >> gfx_pfk.c
echo "\tmemcpy(to_send, \"pfk \", 4);" >> gfx_pfk.c
echo "\tsend_cmd_to_graphics(env, to_send);" >> gfx_pfk.c
echo "\treturn 1;" >> gfx_pfk.c
echo "}" >> gfx_pfk.c
echo "" >> gfx_pfk.c

# pdr
echo "#include \"cmd.h\"" > gfx_pdr.c
echo "" >> gfx_pdr.c
echo "int\tgfx_pdr(t_env *env)" >> gfx_pdr.c
echo "{" >> gfx_pdr.c
echo "\tchar\t*to_send;" >> gfx_pdr.c
echo "" >> gfx_pdr.c
echo "\tto_send = (char*)malloc(4);" >> gfx_pdr.c
echo "\tmemcpy(to_send, \"pdr \", 4);" >> gfx_pdr.c
echo "\tsend_cmd_to_graphics(env, to_send);" >> gfx_pdr.c
echo "\treturn 1;" >> gfx_pdr.c
echo "}" >> gfx_pdr.c
echo "" >> gfx_pdr.c

# pgt
echo "#include \"cmd.h\"" > gfx_pgt.c
echo "" >> gfx_pgt.c
echo "int\tgfx_pgt(t_env *env)" >> gfx_pgt.c
echo "{" >> gfx_pgt.c
echo "\tchar\t*to_send;" >> gfx_pgt.c
echo "" >> gfx_pgt.c
echo "\tto_send = (char*)malloc(4);" >> gfx_pgt.c
echo "\tmemcpy(to_send, \"pgt \", 4);" >> gfx_pgt.c
echo "\tsend_cmd_to_graphics(env, to_send);" >> gfx_pgt.c
echo "\treturn 1;" >> gfx_pgt.c
echo "}" >> gfx_pgt.c
echo "" >> gfx_pgt.c

# pdi
echo "#include \"cmd.h\"" > gfx_pdi.c
echo "" >> gfx_pdi.c
echo "int\tgfx_pdi(t_env *env)" >> gfx_pdi.c
echo "{" >> gfx_pdi.c
echo "\tchar\t*to_send;" >> gfx_pdi.c
echo "" >> gfx_pdi.c
echo "\tto_send = (char*)malloc(4);" >> gfx_pdi.c
echo "\tmemcpy(to_send, \"pdi \", 4);" >> gfx_pdi.c
echo "\tsend_cmd_to_graphics(env, to_send);" >> gfx_pdi.c
echo "\treturn 1;" >> gfx_pdi.c
echo "}" >> gfx_pdi.c
echo "" >> gfx_pdi.c

# enw
echo "#include \"cmd.h\"" > gfx_enw.c
echo "" >> gfx_enw.c
echo "int\tgfx_enw(t_env *env)" >> gfx_enw.c
echo "{" >> gfx_enw.c
echo "\tchar\t*to_send;" >> gfx_enw.c
echo "" >> gfx_enw.c
echo "\tto_send = (char*)malloc(4);" >> gfx_enw.c
echo "\tmemcpy(to_send, \"enw \", 4);" >> gfx_enw.c
echo "\tsend_cmd_to_graphics(env, to_send);" >> gfx_enw.c
echo "\treturn 1;" >> gfx_enw.c
echo "}" >> gfx_enw.c
echo "" >> gfx_enw.c

# eht
echo "#include \"cmd.h\"" > gfx_eht.c
echo "" >> gfx_eht.c
echo "int\tgfx_eht(t_env *env)" >> gfx_eht.c
echo "{" >> gfx_eht.c
echo "\tchar\t*to_send;" >> gfx_eht.c
echo "" >> gfx_eht.c
echo "\tto_send = (char*)malloc(4);" >> gfx_eht.c
echo "\tmemcpy(to_send, \"eht \", 4);" >> gfx_eht.c
echo "\tsend_cmd_to_graphics(env, to_send);" >> gfx_eht.c
echo "\treturn 1;" >> gfx_eht.c
echo "}" >> gfx_eht.c
echo "" >> gfx_eht.c

# ebo
echo "#include \"cmd.h\"" > gfx_ebo.c
echo "" >> gfx_ebo.c
echo "int\tgfx_ebo(t_env *env)" >> gfx_ebo.c
echo "{" >> gfx_ebo.c
echo "\tchar\t*to_send;" >> gfx_ebo.c
echo "" >> gfx_ebo.c
echo "\tto_send = (char*)malloc(4);" >> gfx_ebo.c
echo "\tmemcpy(to_send, \"ebo \", 4);" >> gfx_ebo.c
echo "\tsend_cmd_to_graphics(env, to_send);" >> gfx_ebo.c
echo "\treturn 1;" >> gfx_ebo.c
echo "}" >> gfx_ebo.c
echo "" >> gfx_ebo.c

# edi
echo "#include \"cmd.h\"" > gfx_edi.c
echo "" >> gfx_edi.c
echo "int\tgfx_edi(t_env *env)" >> gfx_edi.c
echo "{" >> gfx_edi.c
echo "\tchar\t*to_send;" >> gfx_edi.c
echo "" >> gfx_edi.c
echo "\tto_send = (char*)malloc(4);" >> gfx_edi.c
echo "\tmemcpy(to_send, \"edi \", 4);" >> gfx_edi.c
echo "\tsend_cmd_to_graphics(env, to_send);" >> gfx_edi.c
echo "\treturn 1;" >> gfx_edi.c
echo "}" >> gfx_edi.c
echo "" >> gfx_edi.c

# seg
echo "#include \"cmd.h\"" > gfx_seg.c
echo "" >> gfx_seg.c
echo "int\tgfx_seg(t_env *env)" >> gfx_seg.c
echo "{" >> gfx_seg.c
echo "\tchar\t*to_send;" >> gfx_seg.c
echo "" >> gfx_seg.c
echo "\tto_send = (char*)malloc(4);" >> gfx_seg.c
echo "\tmemcpy(to_send, \"seg \", 4);" >> gfx_seg.c
echo "\tsend_cmd_to_graphics(env, to_send);" >> gfx_seg.c
echo "\treturn 1;" >> gfx_seg.c
echo "}" >> gfx_seg.c
echo "" >> gfx_seg.c

# smg
echo "#include \"cmd.h\"" > gfx_smg.c
echo "" >> gfx_smg.c
echo "int\tgfx_smg(t_env *env)" >> gfx_smg.c
echo "{" >> gfx_smg.c
echo "\tchar\t*to_send;" >> gfx_smg.c
echo "" >> gfx_smg.c
echo "\tto_send = (char*)malloc(4);" >> gfx_smg.c
echo "\tmemcpy(to_send, \"smg \", 4);" >> gfx_smg.c
echo "\tsend_cmd_to_graphics(env, to_send);" >> gfx_smg.c
echo "\treturn 1;" >> gfx_smg.c
echo "}" >> gfx_smg.c
echo "" >> gfx_smg.c
