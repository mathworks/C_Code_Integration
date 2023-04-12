function setup(html) {

    // Trigger updateButton javascript callback when one ore more public 
    // properties in jsbutton.m get updated
    html.addEventListener("DataChanged", updateButton);

    document.getElementById("b").addEventListener("click", function (event) {
        html.Data = 1;
    });

    function updateButton() {

        // Update button text and icon taking care of alignment
        if ((html.Data.Icon).length == 0){
            var ButtonContent = [
                '<div style="display: flex; justify-content: ' + html.Data.JustifyContent + ';">',
                html.Data.Text,
                '</div>',
            ].join('\n');
        } else {
            var ButtonContent = [
                '<div style="display: flex; gap: 5px; flex-direction: ' + html.Data.FlexDirection + '; align-items: ' + html.Data.AlignItems + '; justify-content: ' + html.Data.JustifyContent + ';">',
                '<img src="images/' + html.Data.Icon + '" height="' + html.Data.IconSize +'" width="' + html.Data.IconSize + '";/>',
                html.Data.Text,
                '</div>',
            ].join('\n');
        }
        document.getElementById("b").innerHTML = ButtonContent;

        // Customize button appearance with CSS
        var StyleProps = [
            'background-color: ' + html.Data.ButtonColor + ';',
            'color: ' + html.Data.FontColor + ';',
            'font-size: ' + html.Data.FontSize + 'px;',
            'font-weight: ' + html.Data.FontWeight + ';',
            'border-radius: ' + html.Data.BorderRadius + 'px;',
            'border-right:' + html.Data.BorderRightThickness + 'px solid ' + html.Data.BorderRightColor + ';',
            'border-top:' + html.Data.BorderTopThickness + 'px solid ' + html.Data.BorderTopColor + ';',
            'border-left:' + html.Data.BorderLeftThickness + 'px solid ' + html.Data.BorderLeftColor + ';',
            'border-bottom:' + html.Data.BorderBottomThickness + 'px solid ' + html.Data.BorderBottomColor + ';',
            'font-family: ' + html.Data.FontName + ';'
        ].join('\n');

        var HoverProps = [
            'button:hover {',
            'background-color: ' + html.Data.HoverButtonColor + ' !important;',
            'color: ' + html.Data.HoverTextColor + '!important;',
            'font-weight: ' + html.Data.HoverFontWeight + ';',
            'text-decoration: ' + html.Data.HoverTextULine + ';', // none or underline
            'border-left:' + html.Data.BorderLeftThickness + 'px solid ' + html.Data.HoverBorderLeftColor + ';',
            'border-bottom:' + html.Data.BorderBottomThickness + 'px solid ' + html.Data.HoverBorderBottomColor + ';',
            'border-top:' + html.Data.BorderTopThickness + 'px solid ' + html.Data.HoverBorderTopColor + ';',
            'border-right:' + html.Data.BorderRightThickness + 'px solid ' + html.Data.HoverBorderRightColor + ';',
            '}'
        ].join('\n');

        // Enable or disable button
        if (html.Data.Enable) {
            EnableProps = [
                'enabled: true;',
                'opacity: 1;',
                'cursor: pointer;',
            ].join('\n');
        } else {
            EnableProps = [
                'enabled: false;',
                'opacity: 0.6;',
                'cursor: not-allowed;',
            ].join('\n');
        }

        // Gather variables above and add new style to the button
        // There should be no need to update the code below
        var style = document.createElement('style');
        NewStyle = ['button {', StyleProps, EnableProps, '}', '', HoverProps].join('\n');
        style.appendChild(document.createTextNode(NewStyle));
        document.getElementById("b").appendChild(style);
        document.getElementById("htmlBody").style.backgroundColor = html.Data.BackgroundColor;
    } // updateButton
} // setup

// Copyright 2023 The MathWorks, Inc.