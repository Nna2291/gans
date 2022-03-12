const changeDirBox = document.querySelectorAll('.menu_box');
const prefs = document.querySelector('.preferences')
const marker = document.querySelector('.marker');

document.addEventListener('click', openMenu);
document.addEventListener('click', changeState);

function openMenu(event) {
    if (event.target.closest('.menu')) {
        for (dirBox of changeDirBox) {
            dirBox.setAttribute('class', 'menu_box disabled');
        }
        id = +event.target.closest('.menu').getAttribute('id') - 1;
        changeDirBox[id].setAttribute('class', 'menu_box');
        prefs.setAttribute('class', 'preferences disabled')
    }
    if (!(event.target.closest('.menu') || event.target.closest('.menu_box'))) {
        for (dirBox of changeDirBox) {
            dirBox.setAttribute('class', 'menu_box disabled');
        }
        prefs.setAttribute('class', 'preferences')
    }
}

function changeState(event) {
    if (event.target.closest('.change_dir_part')) {
        let targ = event.target.closest('.change_dir_part');
        for (butt of targ.parentElement.children) {
            butt.setAttribute('class', 'change_dir_part');
        }
        targ.setAttribute('class', 'change_dir_part active');
        targ.parentElement.parentElement.children[1].innerText = targ.innerText + ' ➤';
    }
}

function positionMarker(x, y, angle) {
    marker.children[0].style.top = x / 100 * 30 + 'rem';
    marker.children[0].style.left = y / 100 * 30 + 'rem';
    marker.children[0].style.rotate = angle + 'deg'
}

// prompt_vars = prompt().split(' ');
// positionMarker(Number(prompt_vars[0]), Number(prompt_vars[1]), Number(prompt_vars[2]));