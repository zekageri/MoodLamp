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