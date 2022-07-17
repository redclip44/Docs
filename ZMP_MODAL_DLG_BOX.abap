*&---------------------------------------------------------------------*
*& Module Pool      ZMP_MODAL_DLG_BOX
*&---------------------------------------------------------------------*
*&
*&---------------------------------------------------------------------*

INCLUDE ZMMDBTOP                                .    " Global Data

data p_car type spfli-carrid.
TABLES: spfli.

* INCLUDE ZMMDBO01                                .  " PBO-Modules
* INCLUDE ZMMDBI01                                .  " PAI-Modules
* INCLUDE ZMMDBF01                                .  " FORM-Routines

*&---------------------------------------------------------------------*
*& Module STATUS_0001 OUTPUT
*&---------------------------------------------------------------------*
*&
*&---------------------------------------------------------------------*
MODULE STATUS_0001 OUTPUT.
* SET PF-STATUS 'xxxxxxxx'.
* SET TITLEBAR 'xxx'.
ENDMODULE.
*&---------------------------------------------------------------------*
*&      Module  USER_COMMAND_0001  INPUT
*&---------------------------------------------------------------------*
*       text
*----------------------------------------------------------------------*
MODULE USER_COMMAND_0001 INPUT.
CASE sy-ucomm.
  WHEN 'DISP'.
    select single * from spfli where carrid = p_car.
      call SCREEN 0002 STARTING AT 10 08 "top left corner co-coordinate
      ENDING AT 70 15. " bottom right corner coordinate
    LEAVE." TO SCREEN 100.
  WHEN 'BACK'.
    LEAVE PROGRAM. "" TO SCREEN 100.
  WHEN 'CANCEL'.
    LEAVE PROGRAM. "" SCREEN.
  WHEN 'EXIT'.
    LEAVE PROGRAM.
  WHEN OTHERS.
    MESSAGE '...' TYPE 'E'.
ENDCASE.
ENDMODULE.