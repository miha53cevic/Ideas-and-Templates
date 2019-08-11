function init() {
    createCanvas(400, 400);

    let r = 50;
    ctx.beginPath();
    ctx.moveTo(WIDTH / 2 + r, HEIGHT / 2);

    for (let t = 0; t <= Math.PI * 2; t += 0.01) {
        x = (WIDTH / 2) + r * Math.cos(t);
        y = (HEIGHT / 2) + r * Math.sin(t);

        ctx.lineTo(x, y);
    }

    ctx.stroke();
}

window.onload = function () {
    init();
}