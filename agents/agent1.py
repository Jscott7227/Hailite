from kaggle_environments.envs.halite.helpers import *
from state import ShipStateMachine
import random
# Returns best direction to move from one position (fromPos) to another (toPos)
# Example: If I'm at pos 0 and want to get to pos 55, which direction should I choose?
def getDirTo(fromPos, toPos, size):
    fromX, fromY = divmod(fromPos[0],size), divmod(fromPos[1],size)
    toX, toY = divmod(toPos[0],size), divmod(toPos[1],size)
    if fromY < toY: return ShipAction.NORTH
    if fromY > toY: return ShipAction.SOUTH
    if fromX < toX: return ShipAction.EAST
    if fromX > toX: return ShipAction.WEST

# Directions a ship can move
directions = [ShipAction.NORTH, ShipAction.EAST, ShipAction.SOUTH, ShipAction.WEST]



# Returns the commands we send to our ships and shipyards
def agent(obs, config):
    size = config.size
    board = Board(obs, config)
    me = board.current_player


    # If there are no ships, use first shipyard to spawn a ship.
    if len(me.ships) == 0 and len(me.shipyards) > 0:
        me.shipyards[0].next_action = ShipyardAction.SPAWN

    # If there are no shipyards, convert first ship into shipyard.
    if len(me.shipyards) == 0 and len(me.ships) > 0:
        me.ships[0].next_action = ShipAction.CONVERT


    ship_pos = [] 
    for ship in me.ships:
        neighbor_pos = [ship.cell.north.position, ship.cell.east.position, 
                    ship.cell.south.position, ship.cell.west.position]
        exploration = random.randint(0,100)
        if ship.next_action == None:
            ship_state = ShipStateMachine()
            if  exploration % 10 == 0:
                ship_state.current_state = ship_state.explore
                ### Part 2: Use the ship's state to select an action
            if ship_state.current_state == ship_state.collect:
                    # If halite at current location running low, 
                    # move to the adjacent square containing the most halite
                if ship.cell.halite < 100:
                        neighbors = [ship.cell.north.halite, ship.cell.east.halite, 
                                    ship.cell.south.halite, ship.cell.west.halite]
                        best = max(range(len(neighbors)), key=neighbors.__getitem__)
                        clear = True 

                        for i in range(4):
                            for ship2 in me.ships:
                                if neighbor_pos[best] in ship_pos or neighbor_pos[best] == ship2.position:
                                    clear = False
                            if clear:
                                ship.next_action = directions[best]
                                ship_pos.append(neighbor_pos[best])
                            else:
                                best = random.randint(0,3)
                if ship.halite > 600:
                    ship_state.current_state = ship_state.deposit

            if ship_state.current_state == ship_state.deposit:
                 # Move towards shipyard to deposit cargo
                direction = getDirTo(ship.position, me.shipyards[0].position, size)
                if direction == ShipAction.NORTH:
                    new_pos = ship.cell.north.position
                if direction == ShipAction.EAST:
                    new_pos = ship.cell.east.position
                if direction == ShipAction.WEST:
                    new_pos = ship.cell.west.position
                if direction == ShipAction.SOUTH:
                    new_pos = ship.cell.south.position
                
                clear = True
                for ship2 in me.ships:
                    if new_pos in ship_pos or new_pos == ship2.position:
                        clear = False
                if clear:
                    ship.next_action = direction
                    ship_pos.append(new_pos)

                if ship.position == me.shipyards[0].position:
                    ship_state.current_state = ship_state.collect

            if ship_state.current_state == ship_state.explore:
                rand = random.randint(0,3)
                clear = True
                for ship2 in me.ships:
                    if neighbor_pos[rand] in ship_pos or neighbor_pos[rand] == ship2.position:
                        clear = False
                if clear:
                    ship.next_action = directions[rand]
                    ship_pos.append(neighbor_pos[rand])
                ship_state.current_state == ship_state.collect
                



    for shipyard in me.shipyards:
        occupied = False
        for ship in me.ships:
            if ship.position == shipyard.position:
                occupied = True
        if not occupied and len(me.ships) < 5:
            shipyard.next_action = ShipyardAction.SPAWN

    return me.next_actions

