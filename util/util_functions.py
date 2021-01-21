def form_tbcnn_model_path(opt):
    model_traits = {}
    model_traits["parser"] = str(opt.parser)
    model_traits["type"] = str(opt.node_type_dim)
    model_traits["token"] = str(opt.node_token_dim)
    model_traits["conv_output"] = str(opt.conv_output_dim)
    model_traits["node_init"] = str(opt.node_init)
    model_traits["num_conv"] = str(opt.num_conv)
    

    model_path = []
    for k, v in model_traits.items():
        model_path.append(k + "_" + v)
    
    return "tbcnn" + "_" + "-".join(model_path)

def form_treecaps_model_path(opt):
    model_traits = {}
    model_traits["parser"] = str(opt.parser)
    model_traits["type"] = str(opt.node_type_dim)
    model_traits["token"] = str(opt.node_token_dim)
    model_traits["conv_output"] = str(opt.conv_output_dim)
    model_traits["init"] = str(opt.node_init)
    model_traits["num_conv"] = str(opt.num_conv)
    model_traits["top_a"] = str(opt.top_a)
    model_traits["sc_num_caps"] = str(opt.static_caps_num_caps)
    model_traits["sc_dim"] = str(opt.static_caps_output_dimension)
    model_traits["cc_dim"] = str(opt.code_caps_output_dimension)
       
    model_path = []
    for k, v in model_traits.items():
        model_path.append(k + "_" + v)
    
    return "treecaps" + "_" + "-".join(model_path)
