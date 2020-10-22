# Simple 2D game demonstrating first attempt at enemy AI

####User Guide
To run the program:
1.	Download and double click on the provided folder ‘AIproject’
2.	Double click on the folder ‘executable’
3.	Double click on ‘AIproject.exe’
Controls:
	Move: Arrow keys
	Shoot: Space bar
	Reset Level: ‘R’
  

###Behavious:
The main controller of the enemies is a finite state machine that cycles through four different states, PATROL, ATTACK, HEAL and DEAD. Each state utilises different steering behaviours and has different exit conditions.

####PATROL (default)  
#####Behaviour: continuously accelerates towards random points around the map (seek) to simulate searching for the player. The player cannot predict where the agents will move next so they must be careful to avoid being spotted.  
#####Exit Condition 1: If the player is within 2 units, the agent will transition to the ATTACK state.  
#####Exit Condition 2: If the player hits the agent with a projectile, the agent will transition to the ATTACK state.  
#####Exit Condition 3: If the agent’s health falls to 0 or below, the agent will transition to the DEAD state.  

####ATTACK  
#####Behaviour: The agent will accelerate to 2 units from the player while shooting projectiles. The agent will calculate the heading of the player in combination with the distance from the player in order to accelerate on a more efficient path (pursue) and to lead the shots which will make the agent more accurate and behave more realistically. If the player comes within 1.5 units of the agent, it will back up in order to maintain its distance of roughly 2 units.  
#####Exit Condition 1: If the agent’s health falls to 2 (40%) or below, the agent will transition to the HEAL state.  
#####Exit Condition 2: If the agent’s health falls to 0 or below, the agent will transition to the DEAD state  

####HEAL  
#####Behaviour: The agent will accelerate towards a health pack (seek) in an attempt of self-preservation.  
#####Exit Condition 1: if the agent successfully picks up the health pack it will transition back to the ATTACK state.  
#####Exit Condition 2: if a health pack is not available i.e. the player or another agent got to it first, the agent will transition back to the ATTACK state.  
#####Exit condition 3: if the agents health falls to 0 or below, the agent will transition to the DEAD state.  

####DEAD  
#####Behaviour: The agent will exhibit no more behaviours and will be removed from the world.  
#####Exit Condition: There is no escaping DEATH.  
