var speed = 4.0;
function mov(a){
    var sx = a.x();
    var sy = a.y();
    var dir = a.direction();
    if(dir == 0){
        sy = sy - speed;
    }
    else if(dir==1){
        sx = sx + speed;

    }
    else if(dir==2){
        sy = sy + speed;
    }
    else if(dir == 3){
        sx = sx - speed;
    }
    a.setPos(sx,sy);
    return "Successful";
}

function movB(a,b){
    var sx = a.x();
    var sy = a.y();
    var status = a.status();
    if(status == 0){
        var size = a.DesSize();
        if(size == 0){
            var dir = b.direction();
            if(dir == 0){
                sy = sy - speed;
            }
            else if(dir==1){
                sx = sx + speed;
        
            }
            else if(dir==2){
                sy = sy + speed;
            }
            else if(dir == 3){
                sx = sx - speed;
            }
        }
        else{
            a.popDes();
            a.change(1);
            var dx = a.Dx();
            var dy = a.Dy();
            if((dy-sy)==0){
                if((dx-sx)>0){
                    sx = sx + speed;
                    a.setDir(1);
                }
                else{
                    sx = sx - speed;
                    a.setDir(3);
                }
            }
            else{
                if((dy-sy)>0){
                    sy = sy + speed;
                    a.setDir(2);
                }
                else{
                    sy = sy-speed;
                    a.setDir(0);
                }
            }
        }
    }
    if(status == 1){
        var dx = a.Dx();
        var dy = a.Dy();
        if(sx==dx && sy == dy){
            var size = a.DesSize();
            if(size == 0){
                a.setDir(b.direction());
                a.change(0);
                var dir = a.direction();
                if(dir == 0){
                    sy = sy - speed;
                }
                else if(dir==1){
                    sx = sx + speed;

                }
                else if(dir==2){
                    sy = sy + speed;
                }
                else if(dir == 3){
                    sx = sx - speed;
                }
            }
            else{
                a.popDes();
                dx = a.Dx();
                dy = a.Dy();
                if((dy-sy)==0){
                    if((dx-sx)>0){
                        sx = sx + speed;
                        a.setDir(1);
                    }
                    else{
                        sx = sx - speed;
                        a.setDir(3);
                    }
                }
                else{
                    if((dy-sy)>0){
                        sy = sy + speed;
                        a.setDir(2);
                    }
                    else{
                        sy = sy-speed;
                        a.setDir(0);
                    }
                }
            }
        }
        else{
            var dir = a.direction();
                if(dir == 0){
                    sy = sy - speed;
                }
                else if(dir==1){
                    sx = sx + speed;

                }
                else if(dir==2){
                    sy = sy + speed;
                }
                else if(dir == 3){
                    sx = sx - speed;
                }
        }
    }
    a.setPos(sx,sy);
    return "Successful";
}
