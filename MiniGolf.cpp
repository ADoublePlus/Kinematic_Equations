/*
    Initially we place the ball at the position (0, Ly∕2) at time t0 = 0.
    The player hits the ball which leaves with initial velocity of magnitude v0 at an angle 𝜃 degrees with the x axis.

    File: MiniGolf.cpp
        - Motion of a free particle in a box: 0 < x < Lx, 
                                              0 < y < Lx.
        - The box is open at x = 0 and has a hole at (xc, yc) of radius R.
        - Ball is shot at (0, Ly/2) with speed v0, angle theta (degrees).
        - Use integration with time step dt: x = x + vx * dt,
                                             y = y + vy * dt.
        - Ball stops in hole (success) or at x = 0 (failure).
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;

auto constexpr M_PI = 3.14159265359;

int main()
{
    // Declaration of variables
    double Lx, Ly, x0, y0, v0x, v0y, t0, tf, dt, t, x, y, vx, vy;
    double v0, theta, xc, yc, R, R2;
    int i, nx, ny;
    string result;
    string buf;

    // Ask user for input
    cout << "# Enter Lx, Ly: \n";
    cin >> Lx >> Ly;
    getline(cin, buf);

    cout << "# Lx = " << Lx << " Ly = " << Ly << endl;

    cout << "# Enter hole position and radius: (xc, yc), R: \n";
    cin >> xc >> yc >> R;
    getline(cin, buf);

    cout << "# (xc, yc) = ( " << xc << " , " << yc << ") " << " R = " << R << endl;

    cout << "# Enter v0, theta(degrees): \n";
    cin >> v0 >> theta;
    getline(cin, buf);

    cout << "# v0 = " << v0 << " theta = " << theta << " degrees " << endl;

    cout << "# Enter dt: \n";
    cin >> dt;
    getline(cin, buf);

    if (Lx <= 0.0)
    {
        cerr << "Lx <= 0\n";
        exit(1);
    }

    if (Ly <= 0.0)
    {
        cerr << "Ly <= 0\n";
        exit(1);
    }

    if (v0 <= 0.0)
    {
        cerr << "v0 <= 0\n";
        exit(1);
    }

    if (abs(theta) > 90.0)
    {
        cerr << "theta > 90 \n";
        exit(1);
    }

    // Initialize
    t0 = 0.0;
    x0 = 0.00001; // Small but non-zero
    y0 = Ly / 2.0;
    R2 = R * R;
    theta = (M_PI / 180.0) * theta;
    v0x = v0 * cos(theta);
    v0y = v0 * sin(theta);

    cout << "# x0 = " << x0 << " y0 = " << y0 << " v0x = " << v0x << " v0y = " << v0y << endl;

    i = 0;
    nx = 0;
    ny = 0;
    t = t0;
    x = x0;
    y = y0;
    vx = v0x;
    vy = v0y;

    ofstream os_file("MiniGolf.dat");
    os_file.precision(17);

    // Compute
    while (true)
    {
        os_file << setw(28) << t << " "
                << setw(28) << x << " " << setw(28) << y << " "
                << setw(28) << vx << " " << setw(28) << vy << '\n';

        i++;
        t = t0 + i * dt;
        x += vx * dt;
        y += vy * dt;

        if (x > Lx)
        {
            vx = -vx;
            nx++;
        }

        if (y < 0.0)
        {
            vy = -vy;
            ny++;
        }

        if (y > Ly)
        {
            vy = -vy;
            ny++;
        }

        if (x <= 0.0)
        {
            result = "Failure";
            break;
        }

        if (((x - xc) * (x - xc) + (y - yc) * (y - yc)) <= R2)
        {
            result = "Success";
            break;
        }
    }

    os_file.close();

    cout << "# Number of collisions: \n";

    cout << "# Result = " << result << " nx = " << nx << " ny = " << ny << endl;

    //getchar();

    exit(0);
}