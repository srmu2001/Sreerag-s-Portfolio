
//SREERAG MURALEEDHARAN

#include"generator.hpp"
#include"Map.hpp"
#include"game.hpp"
#include<vector>
std::vector<Line> lines;
const int MAX_LINES = 50000;

void generateLines()
{
    int genIndex;
  
    
    for (int i = 0; i < MAX_LINES; i++)
    {
        Line line;
        line.z = i * segL;
        genIndex = i / 1203 % 3;

        if (genIndex == 0)
        {
            if (i % 1000 > 300 && i % 1000 < 670)
                line.curve = 2.5; //for right turn in road

            if (i % 1000 > 700 && i % 1000 < 1150)
                line.curve = -2.5; //for left turn in road

            //MOUNTAIN
            if (i >= 7000 && i <= 7943)
            {
                line.y = sin(((i - 7000) / 60.0)) * 4500;

            }
            //WINTER 
            if (i >= 8800 && i <= 9365)
            {
                line.y = sin(((i - 8800) / 60.0)) * 2300;

            }
        }
        if (genIndex == 1)
        {
            
            if (i % 1000 > 800 && i % 1000 < 1000)
                line.curve = 3.5; //for right turn in road

            if (i % 1000 > 300 && i % 1000 < 700)
                line.curve = -3.0;

          //MOUNTAIN
            if (i >= 1203 && i <= 2146)
            {
                line.y = sin(((i - 1203) / 60.0)) * 4500;

            }
          //WINTER
            if (i >= 8800 && i <= 9365)
            {
                line.y = sin(((i - 8800) / 60.0)) * 2300;

            }
        }
        if (genIndex == 2)
        {
            if (i % 1000 > 700 && i % 1000 < 900)
                line.curve = 1.0; //for right turn in road

            if (i % 1000 > 300 && i % 1000 < 500)
                line.curve = -1.0;

            //MOUNTAIN
            if (i >= 7000 && i <= 7943)
            {
                line.y = sin(((i - 7000) / 60.0)) * 4500;

            }
           //WINTNER
            if (i >= 8800 && i <= 9365)
            {
                line.y = sin(((i - 8800) / 60.0)) * 2300;

            }
            if (i >= 2800 && i <= 3365)
            {
                line.y = sin(((i - 2800) / 60.0)) * 2300;

            }       
        }

        lines.push_back(line); //each line is added to VECTOR CONTAINER
    }  
}

void generateObstacles(sf::Sprite ob[])
{

    for (int i = 0; i < MAX_LINES; i++)
    {
       
        //URBAN
        if (i > 0 && i < 1150 && i % 26 == 0)
        {
            lines[i].spriteX = 2.5; lines[i].sprite = ((i / 26) % 2 == 0 ? ob[3] : ob[1]);
        }
        if (i > 0 && i < 1150 && i % 10 == 0)
        {
            lines[i].spriteX = -3.5; lines[i].sprite = ((i / 10) % 2 == 0 ? ob[1] : ob[3]);
        }
        if (i > 4700 && i < 6459 && i % 26 == 0)
        {
            lines[i].spriteX = 2.5; lines[i].sprite = ((i / 26) % 2 == 0 ? ob[3] : ob[1]);
        }
        if (i > 4700 && i < 6459 && i % 10 == 0)
        {
            lines[i].spriteX = -3.5; lines[i].sprite = ((i / 10) % 2 == 0 ? ob[1] : ob[3]);
        }
      
          //MOUNTAIN
        if (i >= 1400 && i <= 2646 && i % 30 == 0)
        {
            lines[i].spriteX = 0.2; lines[i].sprite = ((i / 30) % 2 == 0 ? ob[12] : ob[6]);
        }
        if (i >= 1400 && i <= 2646 && i % 35 == 0)
        {
            lines[i].spriteX = -1.3; lines[i].sprite = ((i / 35) % 2 == 0 ? ob[5] : ob[13]);
        }
        if (i >= 6850 && i <= 8600 && i % 30 == 0)
        {
            lines[i].spriteX = 0.2; lines[i].sprite = ((i / 30) % 2 == 0 ? ob[12] : ob[6]);
        }
        if (i >= 6850 && i <= 8600 && i % 35 == 0)
        {
            lines[i].spriteX = -1.3; lines[i].sprite = ((i / 35) % 2 == 0 ? ob[5] : ob[13]);
        }

        //WINTER
        if (i >= 3000 && i <= 4400 && i % 30 == 0)
        {
            lines[i].spriteX = 0.1; lines[i].sprite = ob[16];
        }
        if (i >= 3000 && i <= 4400 && i % 35 == 0)
        {
            lines[i].spriteX = -1.2; lines[i].sprite =  ob[17];
        }
        if (i >= 8950 && i <= 10680 && i % 30 == 0)
        {
            lines[i].spriteX = 0.1; lines[i].sprite = ob[16];
        }
        if (i >= 8950 && i <= 10680 && i % 35 == 0)
        {
            lines[i].spriteX = -1.2; lines[i].sprite = ob[17];
        }
          
        //BLOSSOM TREE
        if (i > 0 && i < 1150 && i % 75 == 0)
        {
            lines[i].spriteX = -2.1; lines[i].sprite = ob[2];
        } 
        if (i > 0 && i < 1150 && i % 85 == 0)
        {
            lines[i].spriteX = 1; lines[i].sprite = ob[4];
        }
        if (i > 4700 && i < 6459 && i % 75 == 0)
        {
            lines[i].spriteX = -2.1; lines[i].sprite = ob[2];
        } 
        if (i > 4700 && i < 6459 && i % 85 == 0)
        {
            lines[i].spriteX = 1; lines[i].sprite = ob[4];
        }

        //CACTUS
        if (i >= 1400 && i <= 2646 && i % 75 == 0)
        {
            lines[i].spriteX = -2.1; lines[i].sprite = ob[11];
        }    
        if (i >= 1400 && i <= 2646 && i % 85 == 0)
        {
            lines[i].spriteX = 1; lines[i].sprite = ob[14];
        }
        if (i >= 6850 && i <= 8600 && i % 75 == 0)
        {
            lines[i].spriteX = -2.1; lines[i].sprite = ob[11];
        }
        if (i >= 6850 && i <= 8600 && i % 85 == 0)
        {
            lines[i].spriteX = 1; lines[i].sprite = ob[14];
        }

        //PINE
        if(i >= 3000 && i <= 4400 && i % 75 == 0)
        {
            lines[i].spriteX = -2.1; lines[i].sprite = ob[18];
        } 
        if (i >= 3000 && i <= 4400 && i % 85 == 0)
        {
            lines[i].spriteX = 1; lines[i].sprite = ob[19];
        }
        if (i >= 8950 && i <= 10680 && i % 75 == 0)
        {
            lines[i].spriteX = -2.1; lines[i].sprite = ob[18];
        } 
        if (i >= 8950 && i <= 10680 && i % 85 == 0)
        {
            lines[i].spriteX = 1; lines[i].sprite = ob[19];
        }

        //ROAD DIVIEDER
        if (i < 200 && (i % 71) == 0)
        {
           lines[i].spriteX = -0.4; lines[i].sprite = ob[10];
        } 
        if (i > 200 && (i % 101) == 0)
        {
            lines[i].spriteX = -0.4; lines[i].sprite = ob[10];
        }   
        if ((i > 700 && i < 1000) && (i % 71) == 0)
        {
            lines[i].spriteX = 3; lines[i].sprite = ob[10];
        }
        if ((i < 1500 || i>2000) && (i % 71) == 0)
        {
            lines[i].spriteX = -3; lines[i].sprite = ob[10];
        }
        if (i < 800 && (i % 311) == 0)
        {
            lines[i].spriteX = -0.0; lines[i].sprite = ob[10];
        }
        if (i > 501 && (i + 21) % 111 == 0)
        {
            lines[i].spriteX = 0.8; lines[i].sprite = ob[10];
        }
        if ((i > 200 && i < 800) && (i % 81) == 0)
        {
            lines[i].spriteX = -1.2; lines[i].sprite = ob[10];
        }

        //CAR FRONT
        if (i > 800 && (i % 91) == 0)
        {
            lines[i].spriteX = -1.2; lines[i].sprite = ob[8];
        }     
        if (i == 551 || i == 1551 || i == 1951)
        {
            lines[i].spriteX = 0.0; lines[i].sprite = ob[8];
        }
        if (i == 301 || i == 701 || i == 1351 || i == 2291)
        {
            lines[i].spriteX = 0.3; lines[i].sprite = ob[8];
        }
        if (i == 1151 || i == 1751 || i == 2491)
        {
            lines[i].spriteX = -1.2; lines[i].sprite = ob[8];
        }
     
        //CAR BACK//
        if (i == 101 || i == 1651 || i == 2151)
        {
            lines[i].spriteX = -0.0; lines[i].sprite = ob[9];
        }
        if (i == 1251 || i == 1851)
        {
            lines[i].spriteX = 0.3; lines[i].sprite = ob[9];
        }
        if (i == 201 || i == 801 || i == 1453 || i == 2391)
        {
            lines[i].spriteX = -1.0; lines[i].sprite = ob[9];
        }
        
    }
}
void generateLife(sf::Sprite lifee)
{
    for (int i = 0; i < MAX_LINES; i++)
    {
        if ((i % 500) == 0 || (i % 1000) == 0)
        {
            lines[i].lifeX = -0.4; lines[i].life = lifee;
        }  
    }
}