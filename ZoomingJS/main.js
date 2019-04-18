let scale = {
    x: 1,
    y: 1
}

let offset = {
    x: 0,
    y: 0
}

function ScreenToWorld(screenX, screenY) {
    let worldX = screenX / scale.x + offset.x;
    let worldY = screenY / scale.y + offset.y;

    return {
        x: worldX,
        y: worldY
    }
}

function WorldToScreen(worldX, worldY) {
    let screenX = (worldX - offset.x) * scale.x;
    let screenY = (worldY - offset.y) * scale.y;

    return {
        x: screenX,
        y: screenY
    }
}

function drawGrid() {
    clear('white');

    // Horizontal
    for (let i = -HEIGHT / 2; i <= HEIGHT / 2; i++) {
        let a = WorldToScreen(-WIDTH / 2, i);
        let b = WorldToScreen(WIDTH / 2, i);

        line(a.x, a.y, b.x, b.y, 'black');
    }

    // Vertical
    for (let i = -HEIGHT / 2; i <= WIDTH / 2; i++) {
        let a = WorldToScreen(i, -HEIGHT / 2);
        let b = WorldToScreen(i, HEIGHT / 2);

        line(a.x, a.y, b.x, b.y, 'black');
    }
}

window.onload = function () {
    createCanvas(400, 400);

    offset.x = -WIDTH / 2;
    offset.y = -HEIGHT / 2;

    drawGrid();

    document.body.addEventListener('wheel', function (event) {
        let beforeZoom = ScreenToWorld(WIDTH / 2, HEIGHT / 2);

        if (event.deltaY > 0) {
            scale.x *= 0.9;
            scale.y *= 0.9;
        } else if (event.deltaY < 0) {
            scale.x *= 1.1;
            scale.y *= 1.1;
        }

        let afterZoom = ScreenToWorld(WIDTH / 2, HEIGHT / 2);
        offset.x += (beforeZoom.x - afterZoom.x);
        offset.y += (beforeZoom.y - afterZoom.y);

        drawGrid();
    })
}