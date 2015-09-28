#ifndef ADB_STYLE_H_INCLUDED
#define ADB_STYLE_H_INCLUDED
#define ADB_STYLE_H_VERSION "$Id: actions.h,v 1.24 2015/09/28 14:27:27 fabiankeil Exp $"
/*********************************************************************
*
* File        :  adby_style.h
*
* Purpose     :  Delcare some function specific on loading adb syntax 
*                file.
*                And it will be like:
*                Proxy:              urlpattern$proxy@host:port
*                Block:              urlpattern$descriptor
*                Redirect:           urlpattern$r@s@pattern1@pattern2@
*                Text Filter:        ulrpattern$s@pattern1@pattern2@
*
*********************************************************************/


struct action_spec;
struct current_action_spec;
struct client_state;


extern jb_err get_adb_token(char **line, char **name, char **value);// TODO need to confirm that the option array is enough to fit in longs string









#endif