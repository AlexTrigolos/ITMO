const loadTime = function () {
  var t = window.performance.timing;
  var time = (t.domContentLoadedEventEnd - t.navigationStart) / 1000;
  const now = document.getElementById('pload').innerHTML;
  document.getElementById('pload').innerHTML =
    'Total load time: ' +
    now +
    ' ms (client) + ' +
    time.toString() +
    ' секундs (server)';
};
window.addEventListener(
  'load',
  function () {
  loadTime();
    let mas = document.getElementById('menu').getElementsByTagName('a');
  for (let i = 0; i < mas.length; i++) {
      if (mas[i].pathname === document.location.pathname) {
      mas[i].className += " active";
      }
  }
  },
  false,
);
