// ========= ID Mapping ========= //
const mapping = {
  '%E8%BD%A6%E7%A5%A8%E7%A5%A8': ['vip+watch_vip'],
  'Locket': ['Gold']
};

// ========= Fixed Section ========= //
// ========= @NguyenHoa ========= //

var ua = $request.headers["User-Agent"] || $request.headers["user-agent"];
var obj = JSON.parse($response.body);

obj.Attention = "Chúc mừng bạn! Vui lòng không bán hoặc chia sẻ cho người khác!";

var nguyenhoa = {
  is_sandbox: false,
  ownership_type: "PURCHASED",
  billing_issues_detected_at: null,
  period_type: "normal",
  expires_date: "2099-12-18T01:04:17Z",
  grace_period_expires_date: null,
  unsubscribe_detected_at: null,
  original_purchase_date: "2024-07-28T01:04:18Z",
  purchase_date: "2024-07-28T01:04:17Z",
  store: "app_store"
};

var behoa = {
  grace_period_expires_date: null,
  purchase_date: "2024-07-28T01:04:17Z",
  product_identifier: "com.nguyenhoa.premium.yearly",
  expires_date: "2099-12-18T01:04:17Z"
};

const match = Object.keys(mapping).find(key => ua.includes(key));

if (match) {
  let [entitlement, subscription] = mapping[match];
  if (subscription) {
    behoa.product_identifier = subscription;
    obj.subscriber.subscriptions[subscription] = nguyenhoa;
  } else {
    obj.subscriber.subscriptions["com.nguyenhoa.premium.yearly"] = nguyenhoa;
  }
  obj.subscriber.entitlements[entitlement] = behoa;
} else {
  obj.subscriber.subscriptions["com.nguyenhoa.premium.yearly"] = nguyenhoa;
  obj.subscriber.entitlements.pro = behoa;
}

$done({ body: JSON.stringify(obj) });
