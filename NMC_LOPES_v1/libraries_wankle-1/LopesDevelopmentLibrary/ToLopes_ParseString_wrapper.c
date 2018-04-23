

/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif

/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "ToLopes_Common.h"
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 1500
#define y_width 1
/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
 
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output functions
 *
 */
void ToLopes_ParseString_Outputs_wrapper(const uint8_T *s,
			const real_T *s_len,
			real_T *ErrorValue,
			boolean_T *SpringSpringDidntExist,
			boolean_T *BiasForceSpringDidntExist)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
/* Script to parse the answer to the Effects string. The msgID indicates what commands were
sent (see comments inside the sending-string-creation). So we need that to match the answers
to the commands.

ErrorValue: each possible error has its own identifier (see the code), so that a developer
who can read C can find out what was wrong. If an error was detected (i.e., ErrorValue!=0),
then parsing the string is stopped, so part of it was not parsed.
*/
char s_copy[1500];
int l; // The length of s
char *tok;
msgId_type msgId; // see ToLopes_Common.h
int n; // general purpose

ErrorValue[0]= 0;

l = (int)s_len[0];
if (l==0) return;

strncpy(s_copy, s, l);
s_copy[l] = 0;

// Get msgId
tok = strtok(s_copy, ";");
n=sscanf(s, "\"msgID=%u\"", &(msgId.intValue));
if (n==0)
{
	ErrorValue[0]=1;
	return;
}

// Parse answers for createSpringSpring, if they exist
if (msgId.b.create_springspring)
{
	// This part consists of three questions; we're not interested in the answers (not even if they're ---ERROR; only if there are enough answers)
	if ( !(strtok(NULL,";") && strtok(NULL,";") && strtok(NULL,";") ))
	{
		ErrorValue[0]=2;
		return;
	}
}

// Parse answers for createBiasForceSpring, if they exist
if (msgId.b.create_biasforcespring)
{
	// This part consists of 5 questions; we're not interested in the answers (not even if they're ---ERROR; only if there are enough answers)
	if ( !(strtok(NULL,";") && strtok(NULL,";") && strtok(NULL,";") && strtok(NULL,";") && strtok(NULL,";") ))
	{
		ErrorValue[0]=3;
		return;
	}
}

// Parse answers for UpdateMaxForces, if they exist
if (msgId.b.update_max_forces)
{
	// This part consists of 2 requests; we're not interested in the answers (not even if they're ---ERROR; only if there are enough answers)
	if ( !(strtok(NULL,";") && strtok(NULL,";") ))
	{
		ErrorValue[0]=4;
		return;
	}
}

// Parse answers for treadmillvelocity, if they exist
if (msgId.b.treadmill_velocity) 
{
	// This part consists of 1 request; we're not interested in the answer (not even if they're ---ERROR; only if there are enough answers)
	if ( !(strtok(NULL,";")))
	{
		ErrorValue[0]=5;
		return;
	}
}

// Parse answers for enableSprings, if they exist
if (msgId.b.enable_effects) 
{
	// This part consists of 2 requests; we're not interested in the answers (not even if they're ---ERROR; only if there are enough answers)
	if ( !(strtok(NULL,";") && strtok(NULL,";")))
	{
		ErrorValue[0]=6;
		return;
	}
}

SpringSpringDidntExist[0]= false;

if (msgId.b.set_springspringpositions) 
{
	/* This part consists of 3 questions. They're either a positive response: "Effect's position set","Spring's stiffness set"
	* or an error message. If the error message is "--- ERROR: effect 'springspring' does not exist" then we know we need
	* to create the spring next time (and we don't see this as an error because it is allowed to happen by design). 
	* Any other error messages are reported as being an error (and the message is thrown away).
	*/
	tok = strtok(NULL,";");
	if (tok==NULL) { ErrorValue[0] = 7; return; }
	if (strcmp(tok, "\"Effect's position set\"") != 0)
	{
		// Then the output was something different
		if (strcmp(tok, "\"--- ERROR: Effect 'springspring' does not exist\"") == 0) { SpringSpringDidntExist[0]= true;	}
		else { ErrorValue[0] = 8; return; }
	}
}    
 
if (msgId.b.set_springspringvelocities)
{
    tok = strtok(NULL,";");
	if (tok==NULL) { ErrorValue[0] = 22; return; }
	if (strcmp(tok, "\"Effect's velocity set\"") != 0)
	{
		// Then the output was something different
		if (strcmp(tok, "\"--- ERROR: Effect 'springspring' does not exist\"") == 0) { SpringSpringDidntExist[0]= true; } 
		else { ErrorValue[0] = 9; return; }
	}
}

if (msgId.b.set_springspringstiffnesses)
{
	tok = strtok(NULL,";");
	if (tok==NULL) { ErrorValue[0] = 10; return; }
	if (strcmp(tok, "\"Spring10D's stiffness set\"") != 0)
	{
		// Then the output was something different
		if (strcmp(tok, "\"--- ERROR: Effect 'springspring' does not exist\"") == 0) { SpringSpringDidntExist[0]= true; } 
		else { ErrorValue[0] = 11; return; }
	}
}

// Parse answers for BiasForceSpringStiffnesses
if (msgId.b.set_biasforcespring) 
{
	/* This part consists of 1 question. It's either a positive response: "Spring's stiffness set"
	* or an error message. If the error message is "--- ERROR: effect 'biasForceSpring' does not exist" then we know we need
	* to create the spring next time (and we don't see this as an error because it is allowed to happen by design). 
	* Any other error messages are reported as being an error (and the message is thrown away).
	*/
	BiasForceSpringDidntExist[0]= false;
	tok = strtok(NULL,";");
	if (tok==NULL) { ErrorValue[0] = 12; return; }

	if (strcmp(tok, "\"Spring10D's stiffness set\"") != 0)
	{
		// Then the output was something different
		if (strcmp(tok, "\"--- ERROR: Effect 'biasforcespring' does not exist\"") == 0) { BiasForceSpringDidntExist[0]= true; } 
		else { ErrorValue[0] = 13; return; }
	}
}

/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}
