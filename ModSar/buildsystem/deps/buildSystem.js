function buildSystem() {
    this.download = function (url, dist) {
        console.log("download " + url + " to " + dist);
    };
    this.runCmd = function (cmd) {
        console.log('runCmd ' + cmd);
    };
};
module.exports = buildSystem;