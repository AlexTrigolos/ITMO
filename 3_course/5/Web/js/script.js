const loadTime = (function () {
    var t = window.performance.timing;
    var time = (t.domContentLoadedEventEnd - t.navigationStart) / 1000
    document.getElementById("pload").innerHTML = time.toString() + ' секундs';
});
window.addEventListener('load', function () {
    loadTime();
    let mas = document.getElementById('menu').getElementsByTagName('a');
    for (let i = 0; i < mas.length; i++) {
        if (mas[i].pathname === document.location.pathname) {
            mas[i].className += " active";
        }
    }
}, false)