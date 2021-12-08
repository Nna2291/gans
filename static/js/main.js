$(document).ready(function () {


    $("#on").click(function (e) {
        e.preventDefault();
        $.ajax({
            type: "POST",
            url: "/on",
        });
    });
    $("#off").click(function (e) {
        e.preventDefault();
        $.ajax({
            type: "POST",
            url: "/off",
        });
    });
   })
