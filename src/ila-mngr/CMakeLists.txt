# ---------------------------------------------------------------------------- #
# source 
# ---------------------------------------------------------------------------- #
target_sources(${ILANG_LIB_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/p_infer_child_prog_cfg.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/p_map_child_prog_entry.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/v_eq_check.cc
)

