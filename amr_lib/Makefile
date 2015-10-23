

CC = arm-none-linux-gnueabi-gcc


#CC = gcc


DEC_SRC_DIR =  ./amr_nb/dec/src
DEC_INC_DIR =  -I./amr_nb/common/include  -I./amr_nb/dec/src

ENC_SRC_DIR =  ./amr_nb/enc/src
ENC_INC_DIR =  -I./amr_nb/common/include  -I./amr_nb/enc/src

COMMON_SRC_DIR = ./amr_nb/common/src

LOCAL_DEC_SRC_CFILES := \
    	$(DEC_SRC_DIR)/agc.c \
        $(DEC_SRC_DIR)/amrdecode.c \
        $(DEC_SRC_DIR)/a_refl.c \
        $(DEC_SRC_DIR)/b_cn_cod.c \
        $(DEC_SRC_DIR)/bgnscd.c \
        $(DEC_SRC_DIR)/c_g_aver.c \
        $(DEC_SRC_DIR)/d1035pf.c \
        $(DEC_SRC_DIR)/d2_11pf.c \
        $(DEC_SRC_DIR)/d2_9pf.c \
        $(DEC_SRC_DIR)/d3_14pf.c \
        $(DEC_SRC_DIR)/d4_17pf.c \
        $(DEC_SRC_DIR)/d8_31pf.c \
        $(DEC_SRC_DIR)/dec_amr.c \
        $(DEC_SRC_DIR)/dec_gain.c \
        $(DEC_SRC_DIR)/dec_input_format_tab.c \
        $(DEC_SRC_DIR)/dec_lag3.c \
        $(DEC_SRC_DIR)/dec_lag6.c \
        $(DEC_SRC_DIR)/d_gain_c.c \
        $(DEC_SRC_DIR)/d_gain_p.c \
        $(DEC_SRC_DIR)/d_plsf_3.c \
        $(DEC_SRC_DIR)/d_plsf_5.c \
        $(DEC_SRC_DIR)/d_plsf.c \
        $(DEC_SRC_DIR)/dtx_dec.c \
        $(DEC_SRC_DIR)/ec_gains.c \
        $(DEC_SRC_DIR)/ex_ctrl.c \
        $(DEC_SRC_DIR)/if2_to_ets.c \
        $(DEC_SRC_DIR)/int_lsf.c \
        $(DEC_SRC_DIR)/lsp_avg.c \
        $(DEC_SRC_DIR)/ph_disp.c \
        $(DEC_SRC_DIR)/post_pro.c \
        $(DEC_SRC_DIR)/preemph.c \
        $(DEC_SRC_DIR)/pstfilt.c \
        $(DEC_SRC_DIR)/qgain475_tab.c \
        $(DEC_SRC_DIR)/sp_dec.c \
        $(DEC_SRC_DIR)/wmf_to_ets.c	\
        $(DEC_SRC_DIR)/wrapper_dec.c	
 



LOCAL_ENC_SRC_CFILES :=				\
    	$(ENC_SRC_DIR)/amrencode.c \
        $(ENC_SRC_DIR)/autocorr.c \
        $(ENC_SRC_DIR)/c1035pf.c \
        $(ENC_SRC_DIR)/c2_11pf.c \
        $(ENC_SRC_DIR)/c2_9pf.c \
        $(ENC_SRC_DIR)/c3_14pf.c \
        $(ENC_SRC_DIR)/c4_17pf.c \
        $(ENC_SRC_DIR)/c8_31pf.c \
        $(ENC_SRC_DIR)/calc_cor.c \
        $(ENC_SRC_DIR)/calc_en.c \
        $(ENC_SRC_DIR)/cbsearch.c \
        $(ENC_SRC_DIR)/cl_ltp.c \
        $(ENC_SRC_DIR)/cod_amr.c \
        $(ENC_SRC_DIR)/convolve.c \
        $(ENC_SRC_DIR)/cor_h.c \
        $(ENC_SRC_DIR)/cor_h_x2.c \
        $(ENC_SRC_DIR)/cor_h_x.c \
        $(ENC_SRC_DIR)/corrwght_tab.c \
        $(ENC_SRC_DIR)/div_32.c \
        $(ENC_SRC_DIR)/dtx_enc.c \
        $(ENC_SRC_DIR)/enc_lag3.c \
        $(ENC_SRC_DIR)/enc_lag6.c \
        $(ENC_SRC_DIR)/enc_output_format_tab.c \
        $(ENC_SRC_DIR)/ets_to_if2.c \
        $(ENC_SRC_DIR)/ets_to_wmf.c \
        $(ENC_SRC_DIR)/g_adapt.c \
        $(ENC_SRC_DIR)/gain_q.c \
        $(ENC_SRC_DIR)/g_code.c \
        $(ENC_SRC_DIR)/g_pitch.c \
        $(ENC_SRC_DIR)/hp_max.c \
        $(ENC_SRC_DIR)/inter_36.c \
        $(ENC_SRC_DIR)/inter_36_tab.c \
        $(ENC_SRC_DIR)/l_abs.c \
        $(ENC_SRC_DIR)/lag_wind.c \
        $(ENC_SRC_DIR)/lag_wind_tab.c \
        $(ENC_SRC_DIR)/l_comp.c \
        $(ENC_SRC_DIR)/levinson.c \
        $(ENC_SRC_DIR)/l_extract.c \
        $(ENC_SRC_DIR)/lflg_upd.c \
        $(ENC_SRC_DIR)/l_negate.c \
        $(ENC_SRC_DIR)/lpc.c \
        $(ENC_SRC_DIR)/ol_ltp.c \
        $(ENC_SRC_DIR)/pitch_fr.c \
        $(ENC_SRC_DIR)/pitch_ol.c \
        $(ENC_SRC_DIR)/p_ol_wgh.c \
        $(ENC_SRC_DIR)/pre_big.c \
        $(ENC_SRC_DIR)/pre_proc.c \
        $(ENC_SRC_DIR)/prm2bits.c \
        $(ENC_SRC_DIR)/qgain475.c \
        $(ENC_SRC_DIR)/qgain795.c \
        $(ENC_SRC_DIR)/q_gain_c.c \
        $(ENC_SRC_DIR)/q_gain_p.c \
        $(ENC_SRC_DIR)/qua_gain.c \
        $(ENC_SRC_DIR)/s10_8pf.c \
        $(ENC_SRC_DIR)/set_sign.c \
        $(ENC_SRC_DIR)/sid_sync.c \
        $(ENC_SRC_DIR)/sp_enc.c \
        $(ENC_SRC_DIR)/spreproc.c \
        $(ENC_SRC_DIR)/spstproc.c \
        $(ENC_SRC_DIR)/ton_stab.c \
        $(ENC_SRC_DIR)/vad1.c		\
        $(ENC_SRC_DIR)/wrapper_enc.c	



LOCAL_COMMON_SRC_CFILES :=  \
	$(COMMON_SRC_DIR)/add.c 	\
	$(COMMON_SRC_DIR)/az_lsp.c \
	$(COMMON_SRC_DIR)/bitno_tab.c \
	$(COMMON_SRC_DIR)/bitreorder_tab.c \
	$(COMMON_SRC_DIR)/c2_9pf_tab.c	\
	 $(COMMON_SRC_DIR)/div_s.c \
	$(COMMON_SRC_DIR)/extract_h.c \
	$(COMMON_SRC_DIR)/extract_l.c \
	$(COMMON_SRC_DIR)/gains_tbl.c	\
	 $(COMMON_SRC_DIR)/gc_pred.c \
	$(COMMON_SRC_DIR)/get_const_tbls.c \
	$(COMMON_SRC_DIR)/gmed_n.c 	\
	$(COMMON_SRC_DIR)/gray_tbl.c \
	$(COMMON_SRC_DIR)/grid_tbl.c \
	$(COMMON_SRC_DIR)/int_lpc.c \
	$(COMMON_SRC_DIR)/inv_sqrt.c \
	$(COMMON_SRC_DIR)/inv_sqrt_tbl.c \
	$(COMMON_SRC_DIR)/l_deposit_h.c \
	$(COMMON_SRC_DIR)/l_deposit_l.c \
	$(COMMON_SRC_DIR)/log2.c \
	$(COMMON_SRC_DIR)/log2_norm.c \
	$(COMMON_SRC_DIR)/log2_tbl.c \
	$(COMMON_SRC_DIR)/lsfwt.c \
	$(COMMON_SRC_DIR)/l_shr_r.c \
	$(COMMON_SRC_DIR)/lsp_az.c \
	$(COMMON_SRC_DIR)/lsp.c \
	$(COMMON_SRC_DIR)/lsp_lsf.c \
	$(COMMON_SRC_DIR)/lsp_lsf_tbl.c \
	$(COMMON_SRC_DIR)/lsp_tab.c \
	$(COMMON_SRC_DIR)/mult_r.c \
	$(COMMON_SRC_DIR)/negate.c \
	$(COMMON_SRC_DIR)/norm_l.c \
	$(COMMON_SRC_DIR)/norm_s.c \
	$(COMMON_SRC_DIR)/overflow_tbl.c \
	$(COMMON_SRC_DIR)/ph_disp_tab.c \
	$(COMMON_SRC_DIR)/pow2.c \
	$(COMMON_SRC_DIR)/pow2_tbl.c \
	$(COMMON_SRC_DIR)/pred_lt.c \
	$(COMMON_SRC_DIR)/q_plsf_3.c \
	$(COMMON_SRC_DIR)/q_plsf_3_tbl.c \
	$(COMMON_SRC_DIR)/q_plsf_5.c \
	$(COMMON_SRC_DIR)/q_plsf_5_tbl.c \
	$(COMMON_SRC_DIR)/q_plsf.c \
	$(COMMON_SRC_DIR)/qua_gain_tbl.c \
	$(COMMON_SRC_DIR)/reorder.c \
	$(COMMON_SRC_DIR)/residu.c \
	$(COMMON_SRC_DIR)/round.c \
	$(COMMON_SRC_DIR)/set_zero.c \
	$(COMMON_SRC_DIR)/shr.c \
	$(COMMON_SRC_DIR)/shr_r.c \
	$(COMMON_SRC_DIR)/sqrt_l.c \
	$(COMMON_SRC_DIR)/sqrt_l_tbl.c \
	$(COMMON_SRC_DIR)/sub.c \
	$(COMMON_SRC_DIR)/syn_filt.c \
	$(COMMON_SRC_DIR)/weight_a.c \
	$(COMMON_SRC_DIR)/window_tab.c

ALL: ARM_DEC  ARM_ENC

ARM_DEC:
	${CC}  -std=c99  -fpic   -shared  ${DEC_INC_DIR}  ${LOCAL_COMMON_SRC_CFILES}  ${LOCAL_DEC_SRC_CFILES}  -o libamr_dec.so


ARM_ENC:
	${CC}  -std=c99  -fpic   -shared   ${ENC_INC_DIR}  ${LOCAL_COMMON_SRC_CFILES} ${LOCAL_ENC_SRC_CFILES}  -o libamr_enc.so

clean:
	rm -rf  libarm_dec.so    libarm_enc.so

