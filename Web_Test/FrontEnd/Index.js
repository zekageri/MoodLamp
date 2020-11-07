$( document ).ready(function() {
    console.log("A JS file Jqueryvel innentől kezdődik. Ez onpageload-kor történik!");
});
$(function() {
    $('.btn-group-fab').on('click', '.btn', function() {
      $('.btn-group-fab').toggleClass('active');
    });
    $('has-tooltip').tooltip();
  });
  