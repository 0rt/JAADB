const char adb_style_rcs[] = "$Id: actions.c,v 1.92 2013/12/24 13:35:23 fabiankeil Exp $";

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


#include "config.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#ifdef FEATURE_PTHREAD
#include <pthread.h>
#endif

#include "project.h"
#include "jcc.h"
#include "list.h"
#include "actions.h"
#include "adb_style.h"
#include "miscutil.h"
#include "errlog.h"
#include "loaders.h"
#include "encode.h"
#include "urlmatch.h"
#include "cgi.h"
#include "ssplit.h"
#include "filters.h"

const char adb_style_h_rcs[] = ACTIONS_H_VERSION;


/*********************************************************************
*
* Function    :  get_adb_token
*
* Description :  Parses a line for the first action.
*                Modifies its input array, doesn't allocate memory.
*                e.g. given:
*                *line="  +abc{def}  -ghi "
*                Returns:
*                *line="  -ghi "
*                *name="+abc"
*                *value="def"
*
* Parameters  :
*          1  :  line = [in] The line containing the action.
*                       [out] Start of next action on line, or
*                       NULL if we reached the end of line before
*                       we found an action.
*          2  :  name = [out] Start of action name, null
*                       terminated.  NULL on EOL
*          3  :  value = [out] Start of action value, null
*                        terminated.  NULL if none or EOL.
*
* Returns     :  JB_ERR_OK => Ok
*                JB_ERR_PARSE => Mismatched {} (line was trashed anyway)
*
*********************************************************************/
jb_err get_adb_token(char **line, char **name, char **value) {
	char * str = *line;
	char ch;

	/* set default returns */
	*line = NULL;
	*name = NULL;
	*value = NULL;

	/* Eat any leading whitespace */
	while ((*str == ' ') || (*str == '\t'))
	{
		str++;
	}
	/* not allow rule start with $ */
	if(*str == '$') {
		return JB_ERR_PARSE;
	}

	*value = str;
	/* parse url pattern */
	while (((ch = *str) != '\0') &&
		(ch != ' ') && (ch != '\t') && (ch != '$'))
	{

		str++;
	}
	*str = '\0';
	if (ch != '$') {
		/* no option descriptor */
		if (ch == '\0') {
			/* EOL*/
			*line = str;
		}
		else {
			/* add more option for a single url pattern TODO in manner
			 * like url $s@p1@p2@$s@p3@p4@?
			*/
			//*line = str + 1; should I?
		}
		return JB_ERR_OK;
	}
	else {
		++str;
		*name = str;
		while ((ch = *str) != '\0') {
			str++;
		}
		*str = '\0';
		/* got value */
		chomp(*value);
		return JB_ERR_OK;
	}
	return JB_ERR_PARSE;//don't come here
}