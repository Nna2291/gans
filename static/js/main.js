function sendEngineStat(event) {
    flag = 0;
    link = '/engine';
    if (event.target.name.split('_')[0] == 'march') {
        if ($('[name=march_text]')[0].value == 100) {
            flag = 1;
            task1 = "DO;16;17";
            task2 = "DO;16;17";
        }
        else if ($('[name=march_text]')[0].value == 0) {
            flag = 1;
            task1 = "DR;16;17";
            task2 = "DR;16;17";
        }
        else if ($('[name=march_text]')[0].value == 50) {
            flag = 1;
            task1 = "DV;16;17";
            task2 = "DV;16;17";
        }
    }
    else if (event.target.name.split('_')[0] == 'depth') {
        if ($('[name=depth_text]')[0].value == 100) {
            flag = 1;
            task1 = "DO;5;6";
            task2 = "DO;9;15";
        }
        else if ($('[name=depth_text]')[0].value == 0) {
            flag = 1;
            task1 = "DR;5;6";
            task2 = "DR;9;15";
        }
        else if ($('[name=depth_text]')[0].value == 50) {
            flag = 1;
            task1 = "DV;5;6";
            task2 = "DV;9;15";
        }
    }
    else if (event.target.name.split('_')[0] == 'course') {
        if ($('[name=course_text]')[0].value == 100) {
            flag = 1;
            task1 = "DO;3;4";
            task2 = "DR;7;8";
        }
        else if ($('[name=course_text]')[0].value == 0) {
            flag = 1;
            task1 = "DR;3;4";
            task2 = "DO;7;8";
        }
        else if ($('[name=course_text]')[0].value == 50) {
            flag = 1;
            task1 = "DV;3;4";
            task2 = "DV;7;8";
        }
    }
    else if (event.target.name.split('_')[0] == 'lag') {
        if ($('[name=lag_text]')[0].value == 100) {
            flag = 1;
            task1 = "DO;3;4";
            task2 = "DO;7;8";
        }
        else if ($('[name=lag_text]')[0].value == 0) {
            flag = 1;
            task1 = "DR;3;4";
            task2 = "DR;7;8";
        }
        else if ($('[name=lag_text]')[0].value == 50) {
            flag = 1;
            task1 = "DV;3;4";
            task2 = "DV;7;8";
        }
    }

    if (flag) {
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task1})
        });
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task2})
        });
    }
}

document.addEventListener('change', sendEngineStat);