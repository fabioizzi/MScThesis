

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
#include <stdio.h>
#include "ToLopes_Common.h"
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 1
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
void ToLopes_GenerateString_Outputs_wrapper(const boolean_T *UpdateSpringSpringPositions,
			const real_T *SpringPositions,
			const real_T *SpringVelocities,
			const real_T *SpringStiffnesses,
			const real_T *BiasForces,
			const real_T *MaxForces,
			const boolean_T *UpdateMaxForces,
			const real_T *TreadmillVelocity,
			const boolean_T *TreadmillVelocityChanged,
			const boolean_T *CreateSpringSpring,
			const boolean_T *CreateBiasForceSpring,
			const boolean_T *EnableEffects,
			uint8_T *s,
			real_T *s_len)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
/* This script generates the send-string for the effects. It may or may not do the following things:
1 Generate a SpringSpring  (i.e., a spring that interfaces as a spring to the rest of the Simulink model),
  - Also sets maximum forces
2 Generate a BiasForceSpring (i.e., a spring that interfaces as a bias force to the rest of the Simulink model),
  - Also sets maximum forces
  - Also sets position (to something far far away)
3 Update the position and stiffness of the SpringSpring
4 Update the stiffness of the BiasForceSpring (effectively, this sets the bias force)
5, ... some more stuff. It documents itself :-)

Which parts are done is stored in the msgId, so that we have a way of knowing
what the anser is (see also ToLopes_Common.h).
*/

	
/* PARAMETER: BiasForcePosition
We render a bias force F by using a spring with a very far-away equilibrium position P. Then,
by setting the stiffness K such that K = F / P, we get the correct force. Note that stiffnesses
are allowed to be negative, so negative forces are also possible.
*/
#define BIAS_FORCE_POSITION (1.0e3)

const char *createSpringSpringCommands = ";create jointspring SpringSpring;set SpringSpring maxforce [%g,%g,%g,%g,%g,%g,%g,%g,%g,%g];set SpringSpring enable";
const char *createBiasSpringFmt = ";create jointspring BiasForceSpring;set BiasForceSpring maxforce [%g,%g,%g,%g,%g,%g,%g,%g,%g,%g];set BiasForceSpring dampfactor [0,0,0,0,0,0,0,0,0,0];"
		"set BiasForceSpring pos [%g,%g,%g,%g,%g,%g,%g,%g,%g,%g];set BiasForceSpring enable";
const char *commandsUpdateMaxForces = ";set SpringSpring maxforce [%g,%g,%g,%g,%g,%g,%g,%g,%g,%g];set BiasForceSpring maxforce [%g,%g,%g,%g,%g,%g,%g,%g,%g,%g]";
const char *commandsTreadmillVelocity = ";set treadmill %f";
const char *commandsEnableEffects = ";set SpringSpring enable;set BiasForceSpring enable";
const char *commandsSpringSpringPositions = ";set SpringSpring pos [%f,%f,%f,%f,%f,%f,%f,%f,%f,%f]";
const char *commandsSpringSpringVelocities = ";set SpringSpring vel [%f,%f,%f,%f,%f,%f,%f,%f,%f,%f]";
const char *commandsSpringSpringStiffnesses = ";set SpringSpring stiffness [%f,%f,%f,%f,%f,%f,%f,%f,%f,%f]";
const char *commandsBiasForceSpring = ";set BiasForceSpring stiffness [%g,%g,%g,%g,%g,%g,%g,%g,%g,%g]";
char *endOfString = s; // A pointer which we use to keep track of where we can put the next string.

// Create the correct value for msgId

msgId_type msgId;
msgId.intValue = 0; // Set all bits to zero.
msgId.b.create_springspring         = (bool)(CreateSpringSpring[0]);
msgId.b.create_biasforcespring      = (bool)(CreateBiasForceSpring[0]); 
msgId.b.update_max_forces           = (bool)(UpdateMaxForces[0]); 
msgId.b.treadmill_velocity          = (bool)(TreadmillVelocityChanged[0]); 
msgId.b.enable_effects              = (bool)(EnableEffects[0]); 
msgId.b.set_springspringpositions   = (bool)(UpdateSpringSpringPositions[0]);
msgId.b.set_springspringvelocities  = (bool)1; 
msgId.b.set_springspringstiffnesses = (bool)1;
msgId.b.set_biasforcespring         = (bool)1;

endOfString += sprintf(endOfString, "set msgID %u",msgId.intValue);

if (msgId.b.create_springspring)
{
    endOfString += sprintf(endOfString, createSpringSpringCommands,
	    MaxForces[0], MaxForces[1],MaxForces[2], MaxForces[3], MaxForces[4], 
        MaxForces[5],MaxForces[6], MaxForces[7], MaxForces[8], MaxForces[9]);
}

if (msgId.b.create_biasforcespring)
{
    endOfString += sprintf(endOfString, createBiasSpringFmt, 
	MaxForces[0], MaxForces[1], MaxForces[2], MaxForces[3], MaxForces[4], 
    MaxForces[5], MaxForces[6], MaxForces[7], MaxForces[8], MaxForces[9],
	BIAS_FORCE_POSITION,BIAS_FORCE_POSITION,BIAS_FORCE_POSITION,BIAS_FORCE_POSITION,BIAS_FORCE_POSITION,
	BIAS_FORCE_POSITION,BIAS_FORCE_POSITION,BIAS_FORCE_POSITION,BIAS_FORCE_POSITION,BIAS_FORCE_POSITION);
}

if (msgId.b.update_max_forces)
{
    // This is for ramping up the forces of both springs
    endOfString += sprintf(endOfString, commandsUpdateMaxForces,
            MaxForces[0], MaxForces[1], MaxForces[2], MaxForces[3], MaxForces[4],
            MaxForces[5], MaxForces[6], MaxForces[7], MaxForces[8], MaxForces[9],
            MaxForces[0], MaxForces[1], MaxForces[2], MaxForces[3], MaxForces[4],
            MaxForces[5], MaxForces[6], MaxForces[7], MaxForces[8], MaxForces[9]);
}

if (msgId.b.treadmill_velocity)
{
    endOfString += sprintf(endOfString, commandsTreadmillVelocity, TreadmillVelocity[0]);
}

if (msgId.b.enable_effects)
{
    endOfString += sprintf(endOfString, commandsEnableEffects);
}

if (msgId.b.set_springspringpositions)
{
    endOfString += sprintf(endOfString, commandsSpringSpringPositions,
        SpringPositions[0], SpringPositions[1], SpringPositions[2], SpringPositions[3], SpringPositions[4], 
        SpringPositions[5], SpringPositions[6], SpringPositions[7], SpringPositions[8], SpringPositions[9]);
}

if (msgId.b.set_springspringvelocities)
{
    endOfString += sprintf(endOfString, commandsSpringSpringVelocities,
        SpringVelocities[0], SpringVelocities[1], SpringVelocities[2], SpringVelocities[3], SpringVelocities[4],
        SpringVelocities[5], SpringVelocities[6], SpringVelocities[7], SpringVelocities[8], SpringVelocities[9]);
}

if (msgId.b.set_springspringstiffnesses)
{
    // SpringSpringPositions/SpringSpringStiffnesses
    endOfString += sprintf(endOfString, commandsSpringSpringStiffnesses,
    	SpringStiffnesses[0], SpringStiffnesses[1], SpringStiffnesses[2], SpringStiffnesses[3], SpringStiffnesses[4],
        SpringStiffnesses[5], SpringStiffnesses[6], SpringStiffnesses[7], SpringStiffnesses[8], SpringStiffnesses[9]);
}

if (msgId.b.set_biasforcespring)
{   
    // BiasForces
    endOfString += sprintf(endOfString, commandsBiasForceSpring,
    	BiasForces[0]/BIAS_FORCE_POSITION, BiasForces[1]/BIAS_FORCE_POSITION, BiasForces[2]/BIAS_FORCE_POSITION, 
    	BiasForces[3]/BIAS_FORCE_POSITION, BiasForces[4]/BIAS_FORCE_POSITION, BiasForces[5]/BIAS_FORCE_POSITION,
    	BiasForces[6]/BIAS_FORCE_POSITION, BiasForces[7]/BIAS_FORCE_POSITION, BiasForces[8]/BIAS_FORCE_POSITION,
        BiasForces[9]/BIAS_FORCE_POSITION);
}

// Get the length of the spring right
s_len[0] = (double)(endOfString-s); // The length of the string (excluding trailing null character)
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}
