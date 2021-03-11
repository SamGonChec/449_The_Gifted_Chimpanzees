#include "include/gamemanager.h"

GameManager::GameManager(){
    //setting up the menu scene
    Menu menu(&menuScene);

    view.resize(1100,900);
    view.setScene(&menuScene);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.show();

    //Connecting the button to the library signal clicked, along with the slot switchTwoPlayerMode
    connect(menu.returnTwoPlayerPushButton(),SIGNAL(clicked()),this,SLOT(switchTwoPlayerMode()));
}

void GameManager::switchTwoPlayerMode()
{
    //instantiating the game class and scene
    game = new Game(&gameScene);
    view.setScene(&gameScene);
}
