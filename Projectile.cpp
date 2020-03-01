/*
    The user enters the magnitude of the particle's initial velocity and the shooting angle 𝜃 in degrees.
    The initial time is taken to be t0 = 0.
    The program calculates v0x and v0y and prints them to the stdout.
    The data is written to the file Projectile.dat.

    File: Projectile.cpp
        - Shooting a projectile near the earth's surface.
        - No air resistance.
        - Starts at (0, 0), set k, (v0, theta).
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;

auto constexpr M_PI = 3.14159265359;
auto constexpr g = 9.81;

int main()
{
    // Declaration of variables
    double x0, y0, R, x, y, vx, vy, t, tf, dt, k;
    double theta, v0x, v0y, v0;
    string buf;

    // Ask user for input
    cout << "# Enter k, v0, theta (in degrees): \n";
    cin >> k >> v0 >> theta;
    getline(cin, buf);

    cout << "# Enter tf, dt: \n";
    cin >> tf >> dt;
    getline(cin, buf);

    cout << "# k = " << k << endl;
    cout << "# v0 = " << v0 << " theta = " << theta << "o (degrees)" << endl;

    cout << "# t0 = " << 0.0 << " tf = " << tf << " dt = " << dt << endl;

    // Initialize
    if (v0 <= 0.0)
    {
        cerr << "Illegal value of v0 <= 0\n";
        exit(1);
    }

    if (k <= 0.0)
    {
        cerr << "Illegal value of k <= 0\n";
        exit(1);
    }

    if (theta <= 0.0)
    {
        cerr << "Illegal value of theta <= 0\n";
        exit(1);
    }

    if (theta >= 90.0)
    {
        cerr << "Illegal value of theta >= 90\n";
        exit(1);
    }

    theta = (M_PI / 180.0) * theta; // Convert to radians
    v0x = v0 * cos(theta);
    v0y = v0 * sin(theta);

    cout << "# v0x = " << v0x << " v0y = " << v0y << endl;

    ofstream os_file("ProjectileAirResistance.dat");
    os_file.precision(17);

    // Compute
    t = 0.0;

    while (t <= tf)
    {
        x = (v0x / k) * (1.0 - exp(-k * t));
        y = (1.0 / k) * (v0y + (g / k)) * (1.0 - exp(-k * t)) - (g / k) * t;
        vx = v0x * exp(-k * t);
        vy = (v0y + (g / k)) * exp(-k * t) - (g / k);

        os_file << t << " "
                << x << " " << y << " "
                << vx << " " << vy << endl;

        t = t + dt;
    }

    //getchar();

    exit(0);
}