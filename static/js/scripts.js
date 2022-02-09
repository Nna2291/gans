const changeDirBox = document.querySelectorAll('.change_dir_part_box');
const marker = document.querySelector('.marker');

document.addEventListener('click', openMenu);
document.addEventListener('click', changeState);

function openMenu(event) {
    if (event.target.closest('.change_dir')) {
        for (dirBox of changeDirBox) {
            dirBox.setAttribute('class', 'change_dir_part_box disabled');
        }
        id = +event.target.closest('.change_dir').getAttribute('name').slice(1) - 1;
        changeDirBox[id].setAttribute('class', 'change_dir_part_box');
    }
    if (!(event.target.closest('.change_dir') || event.target.closest('.change_dir_part_box'))) {
        for (dirBox of changeDirBox) {
            dirBox.setAttribute('class', 'change_dir_part_box disabled');
        }
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