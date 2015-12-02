# msz
echo "#include \"cmd.h\"" > gfx_msz.c
echo "" >> gfx_msz.c
echo "int\t\tgfx_msz(t_env *env, t_fd *fd, char *cmd)" >> gfx_msz.c
echo "{" >> gfx_msz.c
echo "\tchar\t*to_send;" >> gfx_msz.c
echo "" >> gfx_msz.c
echo "\tto_send = (char*)malloc(4);" >> gfx_msz.c
echo "\tmemcpy(to_send, \"pex \", 4);" >> gfx_msz.c
echo "\tsend_cmd_to_client(fd, to_send);" >> gfx_msz.c
echo "\treturn 1;" >> gfx_msz.c
echo "env = NULL; cmd = NULL;" >> gfx_msz.c
echo "}" >> gfx_msz.c
echo "" >> gfx_msz.c

# bct
echo "#include \"cmd.h\"" > gfx_bct.c
echo "" >> gfx_bct.c
echo "int\t\tgfx_bct(t_env *env, t_fd *fd, char *cmd)" >> gfx_bct.c
echo "{" >> gfx_bct.c
echo "\tchar\t*to_send;" >> gfx_bct.c
echo "" >> gfx_bct.c
echo "\tto_send = (char*)malloc(4);" >> gfx_bct.c
echo "\tmemcpy(to_send, \"pex \", 4);" >> gfx_bct.c
echo "\tsend_cmd_to_client(fd, to_send);" >> gfx_bct.c
echo "\treturn 1;" >> gfx_bct.c
echo "env = NULL; cmd = NULL;" >> gfx_bct.c
echo "}" >> gfx_bct.c
echo "" >> gfx_bct.c

# mct
echo "#include \"cmd.h\"" > gfx_mct.c
echo "" >> gfx_mct.c
echo "int\t\tgfx_mct(t_env *env, t_fd *fd, char *cmd)" >> gfx_mct.c
echo "{" >> gfx_mct.c
echo "\tchar\t*to_send;" >> gfx_mct.c
echo "" >> gfx_mct.c
echo "\tto_send = (char*)malloc(4);" >> gfx_mct.c
echo "\tmemcpy(to_send, \"pex \", 4);" >> gfx_mct.c
echo "\tsend_cmd_to_client(fd, to_send);" >> gfx_mct.c
echo "\treturn 1;" >> gfx_mct.c
echo "env = NULL; cmd = NULL;" >> gfx_mct.c
echo "}" >> gfx_mct.c
echo "" >> gfx_mct.c

# tna
echo "#include \"cmd.h\"" > gfx_tna.c
echo "" >> gfx_tna.c
echo "int\t\tgfx_tna(t_env *env, t_fd *fd, char *cmd)" >> gfx_tna.c
echo "{" >> gfx_tna.c
echo "\tchar\t*to_send;" >> gfx_tna.c
echo "" >> gfx_tna.c
echo "\tto_send = (char*)malloc(4);" >> gfx_tna.c
echo "\tmemcpy(to_send, \"pex \", 4);" >> gfx_tna.c
echo "\tsend_cmd_to_client(fd, to_send);" >> gfx_tna.c
echo "\treturn 1;" >> gfx_tna.c
echo "env = NULL; cmd = NULL;" >> gfx_tna.c
echo "}" >> gfx_tna.c
echo "" >> gfx_tna.c

# ppo
echo "#include \"cmd.h\"" > gfx_ppo.c
echo "" >> gfx_ppo.c
echo "int\t\tgfx_ppo(t_env *env, t_fd *fd, char *cmd)" >> gfx_ppo.c
echo "{" >> gfx_ppo.c
echo "\tchar\t*to_send;" >> gfx_ppo.c
echo "" >> gfx_ppo.c
echo "\tto_send = (char*)malloc(4);" >> gfx_ppo.c
echo "\tmemcpy(to_send, \"pex \", 4);" >> gfx_ppo.c
echo "\tsend_cmd_to_client(fd, to_send);" >> gfx_ppo.c
echo "\treturn 1;" >> gfx_ppo.c
echo "env = NULL; cmd = NULL;" >> gfx_ppo.c
echo "}" >> gfx_ppo.c
echo "" >> gfx_ppo.c

# plv
echo "#include \"cmd.h\"" > gfx_plv.c
echo "" >> gfx_plv.c
echo "int\t\tgfx_plv(t_env *env, t_fd *fd, char *cmd)" >> gfx_plv.c
echo "{" >> gfx_plv.c
echo "\tchar\t*to_send;" >> gfx_plv.c
echo "" >> gfx_plv.c
echo "\tto_send = (char*)malloc(4);" >> gfx_plv.c
echo "\tmemcpy(to_send, \"pex \", 4);" >> gfx_plv.c
echo "\tsend_cmd_to_client(fd, to_send);" >> gfx_plv.c
echo "\treturn 1;" >> gfx_plv.c
echo "env = NULL; cmd = NULL;" >> gfx_plv.c
echo "}" >> gfx_plv.c
echo "" >> gfx_plv.c

# pin
echo "#include \"cmd.h\"" > gfx_pin.c
echo "" >> gfx_pin.c
echo "int\t\tgfx_pin(t_env *env, t_fd *fd, char *cmd)" >> gfx_pin.c
echo "{" >> gfx_pin.c
echo "\tchar\t*to_send;" >> gfx_pin.c
echo "" >> gfx_pin.c
echo "\tto_send = (char*)malloc(4);" >> gfx_pin.c
echo "\tmemcpy(to_send, \"pex \", 4);" >> gfx_pin.c
echo "\tsend_cmd_to_client(fd, to_send);" >> gfx_pin.c
echo "\treturn 1;" >> gfx_pin.c
echo "env = NULL; cmd = NULL;" >> gfx_pin.c
echo "}" >> gfx_pin.c
echo "" >> gfx_pin.c

# pic
echo "#include \"cmd.h\"" > gfx_pic.c
echo "" >> gfx_pic.c
echo "int\t\tgfx_pic(t_env *env, t_fd *fd, char *cmd)" >> gfx_pic.c
echo "{" >> gfx_pic.c
echo "\tchar\t*to_send;" >> gfx_pic.c
echo "" >> gfx_pic.c
echo "\tto_send = (char*)malloc(4);" >> gfx_pic.c
echo "\tmemcpy(to_send, \"pex \", 4);" >> gfx_pic.c
echo "\tsend_cmd_to_client(fd, to_send);" >> gfx_pic.c
echo "\treturn 1;" >> gfx_pic.c
echo "env = NULL; cmd = NULL;" >> gfx_pic.c
echo "}" >> gfx_pic.c
echo "" >> gfx_pic.c

# sgt
echo "#include \"cmd.h\"" > gfx_sgt.c
echo "" >> gfx_sgt.c
echo "int\t\tgfx_sgt(t_env *env, t_fd *fd, char *cmd)" >> gfx_sgt.c
echo "{" >> gfx_sgt.c
echo "\tchar\t*to_send;" >> gfx_sgt.c
echo "" >> gfx_sgt.c
echo "\tto_send = (char*)malloc(4);" >> gfx_sgt.c
echo "\tmemcpy(to_send, \"pex \", 4);" >> gfx_sgt.c
echo "\tsend_cmd_to_client(fd, to_send);" >> gfx_sgt.c
echo "\treturn 1;" >> gfx_sgt.c
echo "env = NULL; cmd = NULL;" >> gfx_sgt.c
echo "}" >> gfx_sgt.c
echo "" >> gfx_sgt.c

# sst
echo "#include \"cmd.h\"" > gfx_sst.c
echo "" >> gfx_sst.c
echo "int\t\tgfx_sst(t_env *env, t_fd *fd, char *cmd)" >> gfx_sst.c
echo "{" >> gfx_sst.c
echo "\tchar\t*to_send;" >> gfx_sst.c
echo "" >> gfx_sst.c
echo "\tto_send = (char*)malloc(4);" >> gfx_sst.c
echo "\tmemcpy(to_send, \"pex \", 4);" >> gfx_sst.c
echo "\tsend_cmd_to_client(fd, to_send);" >> gfx_sst.c
echo "\treturn 1;" >> gfx_sst.c
echo "env = NULL; cmd = NULL;" >> gfx_sst.c
echo "}" >> gfx_sst.c
echo "" >> gfx_sst.c
