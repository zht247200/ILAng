# ---------------------------------------------------------------------------- #
# source 
# ---------------------------------------------------------------------------- #
target_sources(${ILANG_LIB_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/ila_to_plainc.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/plainc_interp.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/plainc_ir.cc
)

