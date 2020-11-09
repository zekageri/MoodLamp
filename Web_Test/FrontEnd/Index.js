$( document ).ready(function() {
  Init_FAB();
  Menu_System_Init();
});

var Page_Before = "Home";
function Init_FAB(){
  $('.btn-group-fab').on('click', '.btn', function() {
    $('.btn-group-fab').toggleClass('active');
  });
  $('has-tooltip').tooltip();
}

function Menu_System_Init(){
  $( ".menutrigg" ).click(function() {
      GoToPage( $(this).attr("title") );
  });
}
function GoToPage(Page){
    if(Page != Page_Before){
       //$("a[title*='"+ Page_Before +"']").removeClass("active");
        $("#"+Page).show();
        $("#"+Page_Before).hide();
        //$("a[title*='"+ Page +"']").addClass("active");
        Page_Before = Page;
    }
}
function getRandom(min, max) {
  return Math.floor(Math.random() * (max - min + 1)) + min;
}           
var canvas = document.getElementById("starfield"),
context = canvas.getContext("2d"),
stars = 800,
colorrange = [0,60,240];
for (var i = 0; i < stars; i++) {
var x = Math.random() * canvas.offsetWidth;
y = Math.random() * canvas.offsetHeight,
radius = Math.random() * 1.2,
hue = colorrange[getRandom(0,colorrange.length - 1)],
sat = getRandom(50,100);
context.beginPath();
context.arc(x, y, radius, 0, 360);
context.fillStyle = "hsl(" + hue + ", " + sat + "%, 88%)";
context.fill();
}