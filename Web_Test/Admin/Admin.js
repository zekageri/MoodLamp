$( document ).ready(function() {
    WSconnect();
    fullHeight();
    Menu_System();
});

var PageBefore = "DashBoard";
function Menu_System(){
    $('.nav-trigger').on('click', function () {
        $(".nav-li").removeClass("active");
        $(this).parent().addClass("active");
        $("#menuIndicator").text($(this).text());
        $("."+PageBefore).hide();
        PageBefore = $(this).text();
        $("."+$(this).text()).show();
        $('#sidebar').toggleClass('active');
    });
    
}
function Connect_After(Millisec){
    setTimeout(function () { WSconnect(); }, Millisec);
}

function WSconnect() {
    var ws = new WebSocket('ws://' + window.location.hostname + '/MoodLamp');
    ws.onopen = function () {
        console.log("Websocket Connected to: " + ws.url);
    };
    ws.onclose = function (e) {
        Connect_After(2000);
    };
    ws.onerror = function (err) {
        ws.close();
        Connect_After(2000);
    };
    ws.onmessage = function (e) {
        Socket_Messages(e);
    };
}

function Socket_Messages(e) {
    if(e.data.includes("InternalTime")){
        var Time = e.data.split(";");
        $("#inttime").text(Time[0]);
    }
}

var fullHeight = function() {
    $('.js-fullheight').css('height', $(window).height());
    $(window).resize(function(){
        $('.js-fullheight').css('height', $(window).height());
    });

    $('#sidebarCollapse').on('click', function () {
        $('#sidebar').toggleClass('active');
      });
};


