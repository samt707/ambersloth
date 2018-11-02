#include "config.h"
#include <epan/prefs.h>
#include <epan/decode_as.h>
#include <wiretap/wtap.h>
#include <stdio.h>
#include <epan/packet.h>
#include <epan/expert.h>

//Not sure
#define DF1_TLV_TYPE 0
#define DF1_TLV_LENGTH 1

#define DF1_TRANS_SYM 1
#define DF1_DST 3

#define DF1_CMD_LOG_READ 0x0fa2;
#define DF1_CMD_LOG_WRITE 0x0faa;


//Call to register protocol with wireshark
void proto_register_df1(void);
void proto_reg_handoff_df1(void);

//Initialize Protocol
static int proto_df1 = -1;

//Initialize Field Names
static int hf_df1_transmission_symbols = -1;
static int hf_df1_dst = -1;
static int hf_df1_src = -1;
static int hf_df1_cmd = -1;
static int hf_df1_sts = -1;
static int hf_df1_tns = -1;
static int hf_df1_fnc = -1;
static int hf_df1_adr = -1;
static int hf_df1_size = -1;
static int hf_df1_data = -1;

//Seems important maybe?? 
static gint ett_df1 = -1;
static gint ett_df1_tlv = -1;

//NOT SURE- Errors maybe??
static expert_field ei_df1_bad_symbol = EI_INIT;

static dissector_handle_t df1_handle;

static const value_string type_vals[] = {
    { DF1_TRANS_SYM, "Transmission Symbol" },
    { DF1_DST, "Destination" },
    { 0, NULL }
};


static const value_string trans_types[] = {
    {0x1001, "DLE SOH" },
    {0x1002, "DLE STX" },
    {0x1003, "DLE ETX" },
    {0x1004, "DLE EOT" },
    {0x1005, "DLE ENQ" },
    {0x1006, "DLE ACK" },
    {0x100F, "DLE NAK" },
    {0x1010, "DLE DLE" },
    {0, NULL}

};

/* Not sure what to do with this
static const string_string ubiquiti_vals[] = {
    {"UP4",     "UP4: UniFi Phone-X"},
    {NULL,       NULL}
};
*/

static int
dissect_df1(tvbuff_t *df1_tvb, packet_info *pinfo, proto_tree *tree, void *data _U_)
{
    proto_tree  *df1_tree, *cmd_tree;
    proto_item  *df1_item; //, *tlv_item;
    //guint32     df1_length;
    //guint32 	df1_type;
    guint32     trans_sym;
    //guint32     symbol;
    guint32 	df1_cmd;
    guint32	df1_fnc;
    short 	df1_cmd_fnc;    

    gint offset = 11;
    //gchar *uValue;
    //const gchar *uModel;


    col_set_str(pinfo->cinfo, COL_PROTOCOL, "DF1");
    col_clear(pinfo->cinfo, COL_INFO);
    col_add_fstr(pinfo->cinfo, COL_INFO, "DF1");

    df1_item = proto_tree_add_item(tree, proto_df1, df1_tvb, 0, -1, ENC_NA);
    df1_tree = proto_item_add_subtree(df1_item, ett_df1);	
    
    proto_tree_add_item_ret_uint(df1_tree, hf_df1_transmission_symbols, df1_tvb, offset, 2, ENC_BIG_ENDIAN, &trans_sym);

    offset+=2;
/*
    if(tvb_reported_length_remaining(df1_tvb, offset+1) <= 0){
        proto_tree_add_item(df1_tree, hf_df1_data, df1_tvb, offset, 1, ENC_BIG_ENDIAN);
    	return tvb_captured_length(df1_tvb);
    }
*/
    while(tvb_reported_length_remaining(df1_tvb, offset) > 0){
	    if(tvb_reported_length_remaining(df1_tvb, offset) == 1){
		proto_tree_add_item(df1_tree, hf_df1_data, df1_tvb, offset, 1, ENC_BIG_ENDIAN);
		return tvb_captured_length(df1_tvb);
	    
	    } 
	    proto_tree_add_item(df1_tree, hf_df1_dst, df1_tvb, offset, 1, ENC_BIG_ENDIAN);
	    
	    proto_tree_add_item(df1_tree, hf_df1_src, df1_tvb, offset + 1, 1, ENC_BIG_ENDIAN);

	    proto_tree_add_item_ret_uint(df1_tree, hf_df1_cmd, df1_tvb, offset + 2, 1, ENC_BIG_ENDIAN, &df1_cmd);
	    proto_tree_add_item(df1_tree, hf_df1_sts, df1_tvb, offset + 3, 1, ENC_BIG_ENDIAN);
	    proto_tree_add_item(df1_tree, hf_df1_tns, df1_tvb, offset + 4, 2, ENC_BIG_ENDIAN);
	    proto_tree_add_item_ret_uint(df1_tree, hf_df1_fnc, df1_tvb, offset + 6, 1, ENC_BIG_ENDIAN, &df1_fnc);
           
	    offset+=7;
 	    df1_cmd_fnc = (df1_cmd << 8) | (df1_fnc);
	    printf("%x\n",df1_cmd_fnc);	
  	    switch(df1_cmd_fnc){
            	case DF1_CMD_LOG_READ:
			cmd_tree = proto_tree_add_subtree(df1_tree, df1_tvb, offset, -1, ett_ubdp_tlv, &tlv_item, "");
			proto_tree_add_item_ret_uint(tlv_tree, hf_ubdp_type, ubdp_tvb, offset + UB_TLV_TYPE, 1, ENC_BIG_ENDIAN, &ubdp_type);
			proto_item_set_text(tlv_tree, "%s", val_to_str_const(ubdp_type, type_vals, "Unknown type"));
			proto_tree_add_item_ret_uint(tlv_tree, hf_ubdp_len, ubdp_tvb, offset + UB_TLV_LENGTH, 2, ENC_BIG_ENDIAN, &ubdp_length);
	    }

	    //proto_item_set_len(tlv_item, df1_length + 3);
            offset += 14;
    }

    return tvb_captured_length(df1_tvb);

}

void
proto_register_df1(void)
{
   
 static hf_register_info hf[] = {
        { &hf_df1_transmission_symbols, {"Transmission Symbols","df1.transmissionsymbol",FT_UINT16, BASE_HEX, VALS(trans_types), 0x0, NULL, HFILL }},
	{ &hf_df1_dst, {"Destination","df1.dst",FT_UINT8, BASE_HEX, NULL, 0x0, NULL, HFILL}},
    	{ &hf_df1_src, {"Source","df1.src", FT_UINT8, BASE_HEX, NULL, 0x0, NULL, HFILL}},
        { &hf_df1_cmd, {"Command","df1.cmd", FT_UINT8, BASE_HEX, NULL, 0x0, NULL, HFILL}},
        { &hf_df1_sts, {"Status Code","df1.sts", FT_UINT8, BASE_HEX, NULL, 0x0, NULL, HFILL}},
        { &hf_df1_tns, {"Transaction Number","df1.tns", FT_UINT16, BASE_HEX, NULL, 0x0, NULL, HFILL}},
        { &hf_df1_fnc, {"Function Code","df1.fnc", FT_UINT8, BASE_HEX, NULL, 0x0, NULL, HFILL}},
	{ &hf_df1_data, {"Data","df1.data",FT_UINT8, BASE_HEX, NULL, 0x0, NULL, HFILL}}
    };

    static gint *ett[] = {
      &ett_df1,
      &ett_df1_tlv
    };
  static ei_register_info ei[] = {
     { &ei_df1_bad_symbol, { "df1.bad_symbol", PI_PROTOCOL, PI_WARN, "Bad Symbol", EXPFILL }}
  };

    expert_module_t* expert_df1;

    proto_df1 = proto_register_protocol("Allen-Bradley DF-1", "DF1", "df1");

    proto_register_field_array(proto_df1, hf, array_length(hf));
    proto_register_subtree_array(ett, array_length(ett));

    expert_df1 = expert_register_protocol(proto_df1);
    expert_register_field_array(expert_df1, ei, array_length(ei));
    register_dissector("df1", dissect_df1, proto_df1);
    df1_handle = create_dissector_handle(dissect_df1, proto_df1);

}

void
proto_reg_handoff_df1(void)
{	
    dissector_add_for_decode_as_with_preference("rtacser.data", df1_handle);
}
