from typing import Any
from kaggle_environments.envs.halite.helpers import *
from statemachine import StateMachine, State

class ShipStateMachine(StateMachine):

    collect = State('collect',initial=True)
    deposit = State('deposit')
    explore = State('explore')
    protect = State('protect')

    return_home  = collect.to(deposit)
    take_land = deposit.to(explore)
    protect_frontline = explore.to(protect)
    ##back_to_grind = protect.to(collect)
    back_to_grind = deposit.to(collect) 


        





    
