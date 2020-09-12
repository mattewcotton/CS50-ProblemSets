let beer_counter = 0;

beer0 = "\n                  ___\n    |\\~~~~~~~~~/|/ _ \\\n    |  |  |  |  | / | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | \\_| |\n    |  |  |  |  |\\___/\n    |\\_|__|__|_/|\n     \\_________/";
beer1 = "\n                  ___\n    |\\_________/|/ _ \\\n    |~~~~~~~~~~~| / | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | \\_| |\n    |  |  |  |  |\\___/\n    |\\_|__|__|_/|\n     \\_________/";
beer2 = "\n                  ___\n    |\\_________/|/ _ \\\n    |  |  |  |  | / | |\n    |~~~~~~~~~~~| | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | \\_| |\n    |  |  |  |  |\\___/\n    |\\_|__|__|_/|\n     \\_________/";
beer3 = "\n                  ___\n    |\\_________/|/ _ \\\n    |  |  |  |  | / | |\n    |  |  |  |  | | | |\n    |~~~~~~~~~~~| | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | \\_| |\n    |  |  |  |  |\\___/\n    |\\_|__|__|_/|\n     \\_________/";
beer4 = "\n                  ___\n    |\\_________/|/ _ \\\n    |  |  |  |  | / | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |~~~~~~~~~~~| | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | \\_| |\n    |  |  |  |  |\\___/\n    |\\_|__|__|_/|\n     \\_________/";
beer5 = "\n                  ___\n    |\\_________/|/ _ \\\n    |  |  |  |  | / | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |~~~~~~~~~~~| | | |\n    |  |  |  |  | \\_| |\n    |  |  |  |  |\\___/\n    |\\_|__|__|_/|\n     \\_________/";
beer6 = "\n                  ___\n    |\\_________/|/ _ \\\n    |  |  |  |  | / | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |~~~~~~~~~~~| \\_| |\n    |  |  |  |  |\\___/\n    |\\_|__|__|_/|\n     \\_________/";
beer7 = "\n                  ___\n    |\\_________/|/ _ \\\n    |  |  |  |  | / | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | \\_| |\n    |~~~~~~~~~~~|\\___/\n    |\\_|__|__|_/|\n     \\_________/";
beer8 = "\n                  ___\n    |\\_________/|/ _ \\\n    |  |  |  |  | / | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | \\_| |\n    |  |  |  |  |\\___/\n    |\\_|__|__|_/|\n     \\_________/";
beer9 = "\n     ¸~~~~~~~~~¸  ___\n    |\\_________/|/ _ \\\n    |  |  |  |  | / | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | | | |\n    |  |  |  |  | \\_| |\n    |  |  |  |  |\\___/\n    |\\_|__|__|_/|\n     \\_________/";

// Function to change the ascii beer image
function beerAnimation()
{
    let beer = document.querySelector('.beer-animation');
    switch(beer_counter)
    {
        case 0:
            beer.innerHTML = beer0;
            beer_counter++;
            break;
        case 1:
            beer.innerHTML = beer1;
            beer_counter++;
            break;
        case 2:
            beer.innerHTML = beer2;
            beer_counter++;
            break;
        case 3:
            beer.innerHTML = beer3;
            beer_counter++;
            break;
        case 4:
            beer.innerHTML = beer4;
            beer_counter++;
            break;
        case 5:
            beer.innerHTML = beer5;
            beer_counter++;
            break;
        case 6:
            beer.innerHTML = beer6;
            beer_counter++;
            break;
        case 7:
            beer.innerHTML = beer7;
            beer_counter++;
            break;
        case 8:
            beer.innerHTML = beer8;
            beer_counter++;
            break;
        case 9:
            beer.innerHTML = beer9;
            beer_counter = 0;
            break;
        default:
            beer_counter = 0;
            break;
    }
}

//itterate through beer animation every 0.25s
window.setInterval(beerAnimation, 500);