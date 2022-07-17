*&---------------------------------------------------------------------*
*& Report ZDEABEE_001
*&---------------------------------------------------------------------*
*& Eben Taljaard
*&---------------------------------------------------------------------*
REPORT ZDEABEE_001.

  DATA:lv_answer,
        rc_return_code type i.
**// TH_POPUP -> F-53
**// Z_CL_DOTNETRUNNER

  CALL FUNCTION 'POPUP_CONTINUE_YES_NO'
    EXPORTING
      textline1 = 'Message 010'
      titel     = 'POPUP_CONTINUE_YES_NO'
    IMPORTING
      answer    = lv_answer.


    CALL METHOD CL_GUI_CFW=>SET_NEW_OK_CODE
      EXPORTING
    NEW_CODE = '0000'
       IMPORTING
    RC       = rc_return_code
  .



  IF lv_answer = 'J'.
    CALL METHOD CL_GUI_CFW=>SET_NEW_OK_CODE
      EXPORTING
    NEW_CODE = '/00'
       IMPORTING
    RC       = rc_return_code
  .
    write 'Btn Yes Used'.
  else.
    write 'Btn No Used'.
  ENDIF.

  // FFFFFF9A

*MESSAGE ID sy-msgid TYPE 'S' NUMBER sy-msgno
*        WITH sy-msgv1 sy-msgv2 sy-msgv3 sy-msgv4 DISPLAY LIKE 'E'.
MESSAGE ID 000 TYPE 'S' NUMBER sy-msgno
        WITH sy-msgv1 sy-msgv2 sy-msgv3 sy-msgv4 DISPLAY LIKE 'E'.

CLEAR sy-debug ##WRITE_OK.