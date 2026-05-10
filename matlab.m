% --- AYARLAR ---
alertApiKey = 'TAK1Jol5qA3+u7B8nnL'; 
alertUrl = "https://api.thingspeak.com/alerts/send";
options = weboptions("HeaderFields", ["ThingSpeak-Alerts-API-Key", alertApiKey]);

% --- VERİ OKUMA ---

data = thingSpeakRead(3373245, 'Fields', 2, 'NumPoints', 1, 'ReadKey', 'FN9NQQ7Z9SXTEH2T');

% --- KARAR VE AKSİYON ---

if ~isempty(data) && data > 37
    subject = "KRİTİK UYARI: Yüksek Vücut Isısı!";
    body = "Vücut ısısı " + string(data) + " dereceye ulaştı.";
    
    try
        webwrite(alertUrl, "body", body, "subject", subject, options);
        fprintf("Mail gönderildi!");
    catch
        fprintf("Mail gönderilemedi, limiti kontrol et.");
    end
end