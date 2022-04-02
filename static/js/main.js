$(document).ready(function () {
    $("#f1").click(function (e) {
        e.preventDefault();
        link = "/on";
        task = "DO;5;6";
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task})
        });
        task = "DO;9;15";
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task})
        });
    });
    $("#f2").click(function (e) {
        e.preventDefault();
        link = "/off";
        task = "DV;5;6";
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task})
        });
        task = "DV;9;15";
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task})
        });
    });
    $("#f3").click(function (e) {
        e.preventDefault();
        link = "/off";
        task = "DR;5;6";
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task})
        });
        task = "DR;9;15";
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task})
        });
    });

    $("#f11").click(function (e) {
        e.preventDefault();
        link = "/on";
        task = "DO;3;4";
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task})
        });
        task = "DO;7;8";
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task})
        });
    });
    $("#f12").click(function (e) {
        e.preventDefault();
        link = "/off";
        task = "DV;3;4";
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task})
        });
        task = "DV;7;8";
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task})
        });
    });
    $("#f13").click(function (e) {
        e.preventDefault();
        link = "/off";
        task = "DR;3;4";
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task})
        });
        task = "DR;7;8";
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task})
        });
    });

    $("#q1").click(function (e) {
        e.preventDefault();
        link = "/on";
        task = "DO;16;17";
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task})
        });
    });
    $("#q3").click(function (e) {
        e.preventDefault();
        link = "/off";
        task = "DV;16;17";
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task})
        });
    });
    $("#q2").click(function (e) {
        e.preventDefault();
        link = "/off";
        task = "DR;16;17";
        $.ajax({
            type: "POST", url: link, contentType: "application/json", data: JSON.stringify({"task": task})
        });
    });
});
